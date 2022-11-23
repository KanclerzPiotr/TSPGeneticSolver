#include <iostream>
#include <3rdParty/cxxopts.hpp>
#include <TSPLibparser.hpp>

std::ifstream openFile(const std::string& filepath) {
    std::ifstream file = std::ifstream(filepath);
    std::cout<< filepath << std::endl;
    if (not file.is_open())
        throw std::runtime_error("File in: " + filepath + "\n cannot be open!");
    return file;
}

int main(int argc, char** argv)
{
    // cxxopts::Options options("TSPGeneticSolver", "Traveling Salesman Problem solver with Genetic algorithm");
    // options.add_options()
    //     ("m,mutation", "Mutation type", cxxopts::value<std::string>()->default_value("SomeType"))
    //     ("c,crossover", "Crossover type", cxxopts::value<std::string>()->default_value("SomeType"))
    //     ("s,selection", "Selection type", cxxopts::value<std::string>()->default_value("SomeType"))
    //     ("i,iterations", "Number of iterations", cxxopts::value<size_t>()->default_value("100"))
    //     ("p,population", "Population size", cxxopts::value<size_t>()->default_value("100"))
    //     ("f,file", "Path to file with problem", cxxopts::value<std::string>())
    //     ("h,help", "Print usage");

    // auto res = options.parse(argc, argv);

    // if (res.count("help"))
    //     std::cout<< options.help() << std::endl;

    // TSPLibparser parser(res["file"].as<std::string>());

    TSPProblem::Problem p;
    // p.setDimension(4);
    // UpperRowMatrixReader reader1(4);
    // auto file = openFile("../tests/upper_row.tsp");
    // p.setData(reader1.readData(file));
    // std::cout<< p << std::endl;

    // LowerRowMatrixReader reader2(4);
    // file = openFile("../tests/lower_row.tsp");
    // p.setData(reader2.readData(file));
    // std::cout<< p << std::endl;

    // UpperRowDiagonalMatrixReader reader3(4);
    // file = openFile("../tests/upper_row_diag.tsp");
    // p.setData(reader3.readData(file));
    // std::cout<< p << std::endl;

    // LowerRowDiagonalMatrixReader reader4(4);
    // file = openFile("../tests/lower_row_diag.tsp");
    // p.setData(reader4.readData(file));
    // std::cout<< p << std::endl;

    // UpperColMatrixReader reader5(4);
    // file = openFile("../tests/upper_col.tsp");
    // p.setData(reader5.readData(file));
    // std::cout<< p << std::endl;

    // LowerColMatrixReader reader6(4);
    // file = openFile("../tests/lower_col.tsp");
    // p.setData(reader6.readData(file));
    // std::cout<< p << std::endl;

    // UpperColDiagonalMatrixReader reader7(4);
    // file = openFile("../tests/upper_col_diag.tsp");
    // p.setData(reader7.readData(file));
    // std::cout<< p << std::endl;

    // LowerColDiagonalMatrixReader reader8(4);
    // file = openFile("../tests/lower_col_diag.tsp");
    // p.setData(reader8.readData(file));
    // std::cout<< p << std::endl;

    Euclidean2DReader reader9(14);
    p.setDimension(14);
    auto file = openFile("../tests/Euclidean2d.tsp");
    p.setData(reader9.readData(file));
    std::cout<< p << std::endl;



    std::cout << "Hello world\n";
    return 0;
}
