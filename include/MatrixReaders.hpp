#ifndef __MATRIXREADERS_H__
#define __MATRIXREADERS_H__

#include "Reader.hpp"

class FullMatrixReader : public Reader {

public:
    FullMatrixReader(int dimension);
    std::vector<int> readData(std::ifstream& file) const override;

};

FullMatrixReader::FullMatrixReader(int dimension) : Reader(dimension) {};

std::vector<int> FullMatrixReader::readData(std::ifstream& file) const {
    std::vector<int> data(dimension * dimension);

    for(int row = 0; row < dimension; ++row)
        for(int col = 0; col < dimension; ++col)
            file >> data[row * dimension + col];

    return data;
}





#endif // __MATRIXREADERS_H__