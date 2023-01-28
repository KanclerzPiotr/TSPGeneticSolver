#ifndef __GENETICFUNCTIONS_H__
#define __GENETICFUNCTIONS_H__

#include <sycl/sycl.hpp>
#include <oneapi/dpl/random>

bool isInRange(int pos, int beg, int end) 
{
    return (pos >= beg && pos < end);
}

int positionInParent(int value, int idx, int pathSize, const sycl::accessor<int, 2, sycl::access_mode::read>& population)
{
    for(int i = 0; i < pathSize; ++i)
    {
        if (value == population[idx][i])
            return i;
    }
    return -1;
}

int corespondingValue(int valueIdx, int idx, const sycl::accessor<int, 2,sycl::access_mode::read>& population)
{
    return population[idx][valueIdx];
}

void fixPMXConflicts(int subrangeStart, int subrangeEnd, 
    const sycl::accessor<int, 2,sycl::access_mode::read>& population, const sycl::accessor<int, 2>& newPopulation, int idx,
    int idxParent1, int idxParent2, int pathSize)
{
    for(int i = subrangeStart; i < subrangeEnd; i++)
    {
        //find first not copied value
        int x = population[idxParent2][i];
        int posInParent = positionInParent(x, idxParent1, pathSize, population); 
        if (isInRange(posInParent, subrangeStart, subrangeEnd))
            continue;
        int idxY = i;
        do {
            int y = corespondingValue(idxY, idxParent1, population);
            idxY = positionInParent(y, idxParent2, pathSize, population);
        }while (isInRange(idxY, subrangeStart, subrangeEnd));
        newPopulation[idx][idxY] = x; 

    }

    for(int i = 0; i < pathSize; i++) { 
        if(newPopulation[idx][i] == -1)
            newPopulation[idx][i] = population[idxParent2][i];
    }
}


void PMXCrossover(oneapi::dpl::ranlux24_base& engine, oneapi::dpl::uniform_real_distribution<float>& distr,
    int pathSize, const sycl::accessor<int, 2, sycl::access_mode::read>& population, const sycl::accessor<int, 2>& newPopulation, int idx, 
    int idxParent1, int idxParent2)
{
    int subrangeStart = distr(engine) * pathSize;
    int subrangeEnd = distr(engine) * pathSize;

    if (subrangeStart > subrangeEnd)
        std::swap(subrangeStart, subrangeEnd);

    for(int i = subrangeStart; i < subrangeEnd; i++){
        newPopulation[idx][i] = population[idxParent1][i];
        newPopulation[idx+1][i] = population[idxParent2][i];
    }

    fixPMXConflicts(subrangeStart, subrangeEnd, population, newPopulation, idx, idxParent1, idxParent2, pathSize);
    fixPMXConflicts(subrangeStart, subrangeEnd, population, newPopulation, idx+1, idxParent2, idxParent1, pathSize);

}

bool isInParent(int x, int idx, int subrangeStart, int subrangeEnd, const sycl::accessor<int, 2, sycl::access_mode::read>& population)
{
    for(int i = subrangeStart; i < subrangeEnd; i++)
    {
        if(x == population[idx][i])
            return true;
    }
    return false;
}

void fixOXConflicts(int idx, int pathSize, int idxParent1, int idxParent2, int subrangeStart, int subrangeEnd, 
    const sycl::accessor<int, 2, sycl::access_mode::read>& population, const sycl::accessor<int, 2>& newPopulation)
{
    int id = subrangeEnd;
    for(int i = 0; i < pathSize; i++) {
        int x = population[idxParent2][i];
        if(!isInParent(x, idxParent1, subrangeStart, subrangeEnd, population))
            newPopulation[idx][(id++)%pathSize] = x;
    }
}

void OXCrossover(oneapi::dpl::ranlux24_base& engine, oneapi::dpl::uniform_real_distribution<float>& distr,
    int pathSize, const sycl::accessor<int, 2, sycl::access_mode::read>& population, const sycl::accessor<int, 2>& newPopulation, int idx,
    int idxParent1, int idxParent2)
{
    int subrangeStart = distr(engine) * pathSize;
    int subrangeEnd = distr(engine) * pathSize;

    if (subrangeStart > subrangeEnd)
        std::swap(subrangeStart, subrangeEnd);

    for(int i = subrangeStart; i < subrangeEnd; i++){
        newPopulation[idx][i] = population[idxParent1][i];
        newPopulation[idx+1][i] = population[idxParent2][i];
    }

    fixOXConflicts(idx, pathSize, idxParent1, idxParent2, subrangeStart, subrangeEnd, population, newPopulation);
    fixOXConflicts(idx+1, pathSize, idxParent2, idxParent1, subrangeStart, subrangeEnd, population, newPopulation);
}


void insertMutation(oneapi::dpl::ranlux24_base& engine, oneapi::dpl::uniform_real_distribution<float>& distr, 
    const sycl::accessor<int, 2>& population, int idx, int pathSize)
{
    if(distr(engine) < 0.1)
    {
        int id = distr(engine) * pathSize;
        int id2 = distr(engine) * pathSize;
        if (id > id2)
            std::swap(id, id2);
        int x = population[idx][id2];
        for(int i = id2 -1; i >= id; i--)
            population[idx][i+1] = population[idx][i];
        population[idx][id] = x;
    }
}

std::pair<int, int> RouletteSelection(oneapi::dpl::ranlux24_base& engine, oneapi::dpl::uniform_real_distribution<float>& distr, 
    const sycl::accessor<float, 1, sycl::access_mode::read>& fitness, int populationSize)
{
    float fitnessSum = fitness[populationSize -1];
            
    float v1 = distr(engine) * fitnessSum;
    float v2 = distr(engine) * fitnessSum;
    int idxParent1 = 0;
    int idxParent2 = 0;
    //find parents
    for(int i = 1; i < populationSize; i++) {
        if (fitness[i - 1] < v1 &&  v1 < fitness[i] )
            idxParent1 = i;
        if (fitness[i - 1] < v2 &&  v2 < fitness[i] )
            idxParent2 = i;    
    }
    return {idxParent1, idxParent2};
}

std::pair<int, int> TournamentSelection(oneapi::dpl::ranlux24_base& engine, oneapi::dpl::uniform_real_distribution<float>& distr,
    const sycl::accessor<float, 1, sycl::access_mode::read>& fitness, int populationSize)
{           
    int best1 = distr(engine) * (populationSize - 1) + 1;
    int best2 = distr(engine) * (populationSize - 1) + 1;
    float best1Fitness = fitness[best1] - fitness[best1 - 1];
    float best2Fitness = fitness[best2] - fitness[best2 - 1];
    for(int i = 0; i < 4; i++)
    {
        int x1 = distr(engine) * (populationSize - 1) + 1;
        int x2 = distr(engine) * (populationSize - 1) + 1;
        float fitness1 = fitness[x1] - fitness[x1 - 1];
        float fitness2 = fitness[x2] - fitness[x2 - 1];
        if(fitness1 > best1Fitness) {
            best1Fitness = fitness1;
            best1 = x1;
        }
        if(fitness2 > best2Fitness) {
            best2Fitness = fitness2;
            best2 = x2;
        }
    }  
    return {best1, best2};
}


#endif // __GENETICFUNCTIONS_H__