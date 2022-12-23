#ifndef __GENETICALGORITHM_H__
#define __GENETICALGORITHM_H__

#include <CL/sycl.hpp>
#include <numeric>
#include <oneapi/dpl/random>
#include <oneapi/dpl/async>
#include <oneapi/dpl/execution>

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int dimension, int population, int iterations, std::vector<int>&& data);

    void run();
    void print();

private:
    void generateRandomPaths(sycl::buffer<int, 2>& pathsBuff);
    void calculateDistances(sycl::buffer<int, 2>& pathsBuff, sycl::buffer<float, 1>& lenghtsBuff, sycl::buffer<int, 2>& distancesBuff);

    int pathSize;
    int iterations;
    int population;
    std::vector<int> distancesVec;
    std::vector<int> pathsVec;
    std::vector<float> lengthsVec;
    std::vector<float> scoreVec;
    int bestPathIndex;
    float bestPathLength;
    sycl::queue q;
};

GeneticAlgorithm::GeneticAlgorithm(int dimension, int population, int iterations, std::vector<int>&& data) : 
    pathSize(dimension),
    iterations(iterations),
    population(population),
    distancesVec(std::move(data)),
    pathsVec(std::vector<int>(pathSize*population)),
    lengthsVec(std::vector<float>(population)),
    scoreVec(std::vector<float>(population)),
    q(sycl::queue{})
{
    std::cout<< "Algorithm running on "<< q.get_device().get_info<sycl::info::device::name>() << std::endl;
}

void GeneticAlgorithm::generateRandomPaths(sycl::buffer<int, 2>& pathsBuff) {
    using namespace sycl;
    int pathSize = this->pathSize;
    q.submit([&](handler& h) {
        accessor paths(pathsBuff, h);

        h.parallel_for(range(population), [=](auto idx) {
            oneapi::dpl::default_engine engine{idx[0]};
            oneapi::dpl::uniform_real_distribution<float> distr{};

            for(int i = 0; i < pathSize; i++){
                paths[idx][i] = i;
            }

            for(int i = pathSize - 1; i >= 0; i--) {
                int m =  distr(engine) * i;
                std::swap(paths[idx][m], paths[idx][i]);
            };
        });
    });
}; 

void GeneticAlgorithm::calculateDistances(sycl::buffer<int, 2>& pathsBuff, sycl::buffer<float, 1>& lenghtsBuff, sycl::buffer<int, 2>& distancesBuff)
{
    using namespace sycl;

    int pathSize = this->pathSize;
    q.submit([&](handler& h) {
        accessor paths(pathsBuff, h, read_only);
        accessor lenghts(lenghtsBuff, h, write_only);
        accessor distances(distancesBuff, h, read_only);

        h.parallel_for(range(population), [=](auto idx) {
            float sum = distances[ paths[idx][pathSize - 1] ][ paths[idx][0] ];
            for(int i = 1; i < pathSize; i++) {
                sum += distances[ paths[idx][i- 1] ][ paths[idx][i] ];
            {
            lenghts[idx] = sum;
        });
    });
}

void GeneticAlgorithm::run()
{
    using namespace sycl;

    auto policy = make_device_policy(q);

    sycl::buffer<int, 2> paths{pathsVec.data(), sycl::range<2>(population, pathSize)};
    sycl::buffer<float, 1> lenghts{lengthsVec};
    sycl::buffer<int, 2> distances{distancesVec.data(), sycl::range<2>(dimension, distances};
    sycl::buffer<float, 1> score{scoreVec};
    
    generateRandomPaths(paths);
    calculateDistances(paths, lenghts, distances);

    auto shortestPathLenght = oneapi::dpl::experimental::reduce_async(policy, dpl::begin(lenghts), dpl::end(lenghts), 
        std::numeric_limits<float>::max(), std::min<float>()).get();

    //calculate fittnes
    oneapi::dpl::experimental::transform_async(policy, dpl::begin(lenghts), dpl::end(lenghts), dpl::begin(score), [shortestPathLenght](float lenght){ return shortestPathLenght/lenght; }))
    int sum = oneapi::dpl::experimental::reduce_async(policy, dpl::begin(lenghts), dpl::end(lenghts), ).get();





}

void GeneticAlgorithm::print()
{
    for(int i = 0; i < population; i++)
    { 
        std::cout << "[";
        for(int j = 0; j < pathSize; j++)
        {
            std::cout<< pathsVec[i* pathSize + j] << ", ";
        }
        std::cout<< "]\n";
    }
}

#endif // __GENETICALGORITHM_H__