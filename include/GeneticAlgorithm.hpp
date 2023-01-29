#ifndef __GENETICALGORITHM_H__
#define __GENETICALGORITHM_H__

#include <sycl/sycl.hpp>
#include <numeric>
#include <algorithm>
#pragma clang diagnostic push 
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <oneapi/dpl/random>
#include <oneapi/dpl/execution>
#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/async>
#pragma clang diagnostic pop

#include "GeneticFunctions.hpp"

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int dimension, int population, int iterations, std::vector<int>&& data);

    void run();
    void print();

private:
    void generatePopulation(sycl::buffer<int, 2>& pathsBuff);
    void generateNewPopulation(sycl::buffer<int, 2>& populationBuff, sycl::buffer<int, 2>& newPopulationBuff, sycl::buffer<float, 1>& fitnessBuff);
    void calculateDistances(sycl::buffer<int, 2>& pathsBuff, sycl::buffer<float, 1>& lenghtsBuff, sycl::buffer<int, 2>& distancesBuff);

    int pathSize;
    int iterations;
    int populationSize;
    std::vector<int> neighborsMatrixVec;
    std::vector<int> populationVec;
    std::vector<int> newPopulationVec;
    std::vector<float> lengthVec;
    std::vector<float> fitnessVec;
    
    std::vector<int> bestPath;
    float bestPathLength;
    sycl::queue q;
};

GeneticAlgorithm::GeneticAlgorithm(int dimension, int population, int iterations, std::vector<int>&& data) : 
    pathSize(dimension),
    iterations(iterations),
    populationSize(population),
    neighborsMatrixVec(std::move(data)),
    populationVec(std::vector<int>(pathSize*population)),
    newPopulationVec(std::vector<int>(pathSize*population)),
    lengthVec(std::vector<float>(population)),
    fitnessVec(std::vector<float>(population)),
    bestPath(std::vector<int>(pathSize)),
    bestPathLength(std::numeric_limits<float>::max()),
    q(sycl::queue{sycl::cpu_selector_v})
{
    // std::cout<< "Algorithm running on "<< q.get_device().get_info<sycl::info::device::name>() << std::endl;
}

void GeneticAlgorithm::generatePopulation(sycl::buffer<int, 2>& populationBuff) {
    using namespace sycl;
    int pathSize = this->pathSize;
    q.submit([&](handler& h) {
        accessor population(populationBuff, h);


        h.parallel_for(range(populationSize), [=](auto idx) {
            oneapi::dpl::ranlux24_base engine{(idx[0]*pathSize )^pathSize};
            oneapi::dpl::uniform_real_distribution<float> distr{};

            for(int i = 0; i < pathSize; i++){
                population[idx][i] = i;
            }
            
            for(int i = pathSize-1; i > 0; i--) {
                int m =  distr(engine) * i;
                std::swap(population[idx][m], population[idx][i]);
            };
        });
    });
}; 

void GeneticAlgorithm::calculateDistances(sycl::buffer<int, 2>& populationBuff, sycl::buffer<float, 1>& lenghtBuff, sycl::buffer<int, 2>& neighborsMatrixBuff)
{
    using namespace sycl;

    int pathSize = this->pathSize;
    q.submit([&](handler& h) {
        accessor population(populationBuff, h, read_only);
        accessor lenght(lenghtBuff, h, write_only);
        accessor neighbors(neighborsMatrixBuff, h, read_only);

        h.parallel_for(range(populationSize), [=](auto idx) {
            float sum = neighbors[ population[idx][pathSize - 1] ][ population[idx][0] ];
            for(int i = 1; i < pathSize; i++) {
                sum += neighbors[ population[idx][i- 1] ][ population[idx][i] ];
            }
            lenght[idx] = sum;
        });
    });
}

void GeneticAlgorithm::generateNewPopulation(sycl::buffer<int, 2>& populationBuff, sycl::buffer<int, 2>& newPopulationBuff, sycl::buffer<float, 1>& fitnessBuff) {

    using namespace sycl;
    
    int pathSize = this->pathSize;
    int populationSize = this->populationSize;

    q.submit([&](handler& h) {
        accessor population(populationBuff, h, read_only);
        accessor newPopulation(newPopulationBuff, h);
        accessor fitness(fitnessBuff, h, read_only);
        h.parallel_for(range(populationSize/2), [=](id<1> id) {

            oneapi::dpl::ranlux24_base engine{id[0]};
            oneapi::dpl::uniform_real_distribution<float> distr{};

            int idx = id[0] * 2;

            for(int i =0; i < pathSize; i++) {
                newPopulation[idx][i] = -1;
                newPopulation[idx+1][i] = -1;
            }

            auto [idxParent1, idxParent2] = TournamentSelection(engine, distr, fitness, populationSize);

            OXCrossover(engine, distr, pathSize, population, newPopulation, idx, idxParent1, idxParent2);

            insertMutation(engine, distr, newPopulation, idx, pathSize);
            
        });
    }).wait();
}

void GeneticAlgorithm::run()
{
    using namespace sycl;
    using namespace oneapi::dpl;
    using namespace oneapi::dpl::execution;

    auto policy = make_device_policy(q);

    // paths - permutations
    buffer<int, 2> population{populationVec.data(), range<2>(populationSize, pathSize)};
    buffer<int, 2> newPopulation{newPopulationVec.data(), range<2>(populationSize, pathSize)};
    buffer<float, 1> lenght{lengthVec};
    buffer<int, 2> neighborsMatrix{neighborsMatrixVec.data(), range<2>(pathSize, pathSize)};
    buffer<float, 1> fitness{fitnessVec};
    
    // std::cout << "Generating" << std::endl;
    auto start1 = std::chrono::steady_clock::now();
    generatePopulation(population);
    for(int i = 0; i < iterations; ++i) {
        // std::cout << "Calculating distances" << std::endl;
        auto start = std::chrono::steady_clock::now();
        calculateDistances(population, lenght, neighborsMatrix);

        {
            // host_accessor host(population, read_only);
            // host_accessor lenght_acc(lenght, read_only);
            // for(int i = 0; i < populationSize; i++) {
            //     for(int j = 0; j < pathSize; j++) {
            //         std::cout << host[i][j] << ", ";
            //     }
            //     std::cout << " - " << lenght_acc[i] << std::endl;
            // }
        }

        // std::cout << "Finding shortest path length" << std::endl;
        auto currentBestPathIterator = min_element(policy, begin(lenght), end(lenght));  
        float currentBestPathLength;
        int currentBestPathIndex;
        {
            currentBestPathIndex = std::distance(begin(lenght), currentBestPathIterator);
            host_accessor lenght_acc(lenght, read_only);
            currentBestPathLength = lenght_acc[currentBestPathIndex];
            // std::cout<< " Current best path length: "<< currentBestPathLength 
            //     << " Current best path index: " << currentBestPathIndex << " Best path length " << bestPathLength << std::endl;
        }

        // std::cout<< "Calculating fittness " <<std::endl;
        transform_inclusive_scan(policy, begin(lenght), end(lenght), begin(fitness), 
            std::plus<float>{},
            [currentBestPathLength](float lenght){ return pow(currentBestPathLength/lenght, 5); });

        if (currentBestPathLength < bestPathLength)
        {
            // std::cout << "New best found: " << currentBestPathLength << std::endl;
            bestPathLength = currentBestPathLength;
            host_accessor host{population, read_only};
            for(int i = 0; i < pathSize; i++)
                bestPath[i] = host[currentBestPathIndex][i];
        }
        // std::cout << " Waiting for fitness" << std::endl;
        

        // std::cout << " Generating new population" << std::endl;
        generateNewPopulation(population, newPopulation, fitness);


        std::swap(population, newPopulation);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << elapsed_seconds.count() << "\n";
    }
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = end1-start1;
    std::cout << "elapsed time: " << elapsed_seconds1.count() << "s\n";



}

void GeneticAlgorithm::print()
{
    for(int i = 0; i < populationSize; i++)
    { 
        std::cout << "[";
        for(int j = 0; j < pathSize; j++)
        {
            std::cout<< populationVec[i* pathSize + j] << ", ";
        }
        std::cout<< "]\n";
    }
}

#endif // __GENETICALGORITHM_H__