#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include <string>
#include <vector>

#include <TSPSpecification.hpp>



namespace TSPProblem {

class Problem {

    friend std::ostream& operator<<(std::ostream& os, const Problem& problem);

public:
    void setName(const std::string& name);
    void setType(const TYPE type);
    void setComment(const std::string& comment);
    void setDimension(int);
    void setData(std::vector<int>&& data);

private:
    std::string name;
    std::string comment;
    TYPE type;
    int dimension = 0;
    std::vector<int> data;
};

std::ostream& operator<<(std::ostream& os, const Problem& problem)
{
    for(int row = 0; row < problem.dimension; ++row, std::cout<< "\n")
        for(int col = 0; col < problem.dimension; ++col)
            os << problem.data[row * problem.dimension + col] << "\t";
    return os;
}

void Problem::setData(std::vector<int>&& data)
{
    this->data = std::move(data);
    std::cout<<this->data.data() << std::endl;
}

void Problem::setName(const std::string& name)
{
    this->name = std::move(name);
}

void Problem::setType(const TYPE type)
{
    this->type = type;
}

void Problem::setComment(const std::string& comment)
{
    this->comment += comment;
}

void Problem::setDimension(int dimension)
{
    this->dimension = dimension;
}
} // namespace TSPProblem


#endif // __PROBLEM_H__