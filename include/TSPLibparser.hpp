#ifndef __TSPLIBPARSER_H__
#define __TSPLIBPARSER_H__



#include <string>
#include <fstream>
#include <Problem.hpp>

class TSPLibparser
{
public:
    TSPLibparser(const std::string& filepath);
    ~TSPLibparser() = default;

private:
    void openFile();
    void readfile();

    void setName();
    void setType();
    void setComment();
    
    const std::string filepath;
    std::ifstream file;
    TSPProblem::Problem problem;


};

void TSPLibparser::openFile() {
    file = std::ifstream(filepath);
    std::cout<< filepath << std::endl;
    if (not file.is_open())
        throw std::runtime_error("File in: " + filepath + "\n cannot be open!");
}

TSPLibparser::TSPLibparser(const std::string& filepath) :
    filepath(filepath)
{
    openFile();

    readfile();
}

void TSPLibparser::setName()
{
    std::string name;
    file >> name;
    std::cout<<name << std::endl;
    problem.setName(name);
            
}

void TSPLibparser::setType()
{
    std::string type;
    file >> type;
    std::cout<< type << std::endl;
    problem.setType(TSPProblem::typeStrToEnum[type]);
}

void TSPLibparser::setComment()
{
    std::string line;
    std::getline(file, line);
    std::cout << line;
}

void TSPLibparser::readfile()
{
    using namespace TSPProblem;
    std::string word;
    while(!file.eof())
    {
        file >> word;
        switch (specificationStrToEnum[word])
        {
        case SPECIFICATION::NAME:
            setName();
            break;
        case SPECIFICATION::TYPE:
            setType(); 
            break;
        case SPECIFICATION::COMMENT: 
            setComment();
            break;
        case SPECIFICATION::DIMENSION: 
            break;
        case SPECIFICATION::CAPACITY: 
            break;
        case SPECIFICATION::EDGE_WEIGHT_TYPE: 
            break;
        case SPECIFICATION::EDGE_WEIGHT_FORMAT: 
            break;
        case SPECIFICATION::EDGE_DATA_FORMAT: 
            break;
        case SPECIFICATION::NODE_COORD_TYPE: 
            break;
        case SPECIFICATION::DISPLAY_DATA_TYPE: 
            break;
        case SPECIFICATION::NODE_COORD_SECTION: 
            break;
        case SPECIFICATION::DEPOT_SECTION: 
            break;
        case SPECIFICATION::DEMAND_SECTION: 
            break;
        case SPECIFICATION::EDGE_DATA_SECTION: 
            break;
        case SPECIFICATION::FIXED_EDGES_SECTION: 
            break;
        case SPECIFICATION::DISPLAY_DATA_SECTION: 
            break;
        case SPECIFICATION::TOUR_SECTION: 
            break;
        case SPECIFICATION::EDGE_WEIGHT_SECTION: 
            break;
        default:
            break;
        }
    }
}



#endif // __TSPLIBPARSER_H__