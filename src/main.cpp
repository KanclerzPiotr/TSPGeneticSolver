#include <iostream>
#include <3rdParty/cxxopts.hpp>
#include <TSPLibparser.hpp>
#include <GeneticAlgorithm.hpp>



void parseArgs(int argc, char **argv)
{

}

int main(int argc, char** argv)
{
    cxxopts::Options options("TSPGeneticSolver", "Traveling Salesman Problem solver with Genetic algorithm");
    options.add_options()
        ("m,mutation", "Mutation type", cxxopts::value<std::string>()->default_value("SomeType"))
        ("c,crossover", "Crossover type", cxxopts::value<std::string>()->default_value("SomeType"))
        ("s,selection", "Selection type", cxxopts::value<std::string>()->default_value("SomeType"))
        ("i,iterations", "Number of iterations", cxxopts::value<size_t>()->default_value("100"))
        ("p,population", "Population size", cxxopts::value<size_t>()->default_value("100"))
        ("f,file", "Path to file with problem", cxxopts::value<std::string>())
        ("h,help", "Print usage");

    auto res = options.parse(argc, argv);

    if (res.count("help"))
        std::cout<< options.help() << std::endl;

    // parseArgs(argc, argv);
    TSPLibparser parser(res["file"].as<std::string>());
    auto problem = parser.getProblem();

    GeneticAlgorithm algorithm(problem.dimension, 100000, 1000, std::move(problem.data));

    algorithm.run();

    // algorithm.print();
    return 0;
}


