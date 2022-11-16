#ifndef __TSPLIBPARSER_H__
#define __TSPLIBPARSER_H__



#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <Problem.hpp>

#include "ReaderFactory.hpp" 

class TSPLibparser
{
public:
    TSPLibparser(const std::string& filepath);
    ~TSPLibparser() = default;

private:
    void openFile();
    void readfile();

    std::pair<std::string, std::string> parseLine(const std::string& word);
    void setName(const std::string& name);
    void setType(const std::string& type);
    void setComment(const std::string& text);
    
    const std::regex specification_regex = std::regex("^[A-Z_]+");
    const std::regex value_regex = std::regex(": ([a-zA-Z0-9_ ,./\"]+)$");
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

std::pair<std::string, std::string> TSPLibparser::parseLine(const std::string& line)
{
    std::smatch specification;
    std::smatch value;
    std::regex_search(line, specification, specification_regex);
    std::regex_search(line, value, value_regex);
    return {specification[0], value[1]};
}

void TSPLibparser::readfile()
{
    using namespace TSPProblem;
    std::string line;
    EDGE_WEIGHT_TYPE weightType;
    EDGE_WEIGHT_FORMAT weightFormat;
    int dimension;
    while(!file.eof())
    {
        getline(file, line);
        auto [specification, value] = parseLine(line);
        switch (specificationStrToEnum[specification])
        {
        case SPECIFICATION::NAME:
            problem.setName(value);
            break;
        case SPECIFICATION::TYPE:
            problem.setType(typeStrToEnum[value]);
            break;
        case SPECIFICATION::COMMENT: 
            problem.setComment(value);
            break;
        case SPECIFICATION::DIMENSION:
            dimension = std::stoi(value);
            problem.setDimension(dimension);
            break;
        case SPECIFICATION::CAPACITY: 
            throw std::runtime_error("Not implemented yet");
            break;
        case SPECIFICATION::EDGE_WEIGHT_TYPE: 
            weightType = edgeWeightTypeStrToEnum[value];
            break;
        case SPECIFICATION::EDGE_WEIGHT_FORMAT: 
            weightFormat = edgeWeightFormatStrToEnum[value];
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
            throw std::runtime_error("Not implemented yet");
            break;
        case SPECIFICATION::EDGE_WEIGHT_SECTION: 
            ReaderFactory::makeReader(dimension, weightType, weightFormat);
            break;
        default:
            break;
        }
    }
}



#endif // __TSPLIBPARSER_H__