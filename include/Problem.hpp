#ifndef __PROBLEM_H__
#define __PROBLEM_H__

#include <string>
#include <vector>

#include <TSPSpecification.hpp>



namespace TSPProblem {

class Problem {
public:
    void setName(const std::string& name);
    void setType(const TYPE type);
    void setComment(const std::string& comment);
    void setDimension(int);

private:
    std::string name;
    std::string comment;
    TYPE type;
    int dimension = 0;
    std::vector<int> data;
};

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