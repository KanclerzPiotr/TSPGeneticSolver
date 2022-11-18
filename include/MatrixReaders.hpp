#ifndef __MATRIXREADERS_H__
#define __MATRIXREADERS_H__

#include "Reader.hpp"

class FullMatrixReader : public Reader {
public:
    FullMatrixReader(int dimension);
    ~FullMatrixReader() = default;
    std::vector<int> readData(std::ifstream& file) const override;
};

class UpperRowMatrixReader : public Reader {
public:
    UpperRowMatrixReader(int dimension);
    ~UpperRowMatrixReader() = default;
    std::vector<int> readData(std::ifstream& file) const override;
};

class LowerRowMatrixReader : public Reader {
public:
    LowerRowMatrixReader(int dimension);
    ~LowerRowMatrixReader() = default;
    std::vector<int> readData(std::ifstream& file) const override;
};

class UpperRowDiagonalMatrixReader : public Reader {
public:
    UpperRowDiagonalMatrixReader(int dimension);
    ~UpperRowDiagonalMatrixReader() = default;
    std::vector<int> readData(std::ifstream& file) const override;
};

class LowerRowDiagonalMatrixReader : public Reader {
public:
    LowerRowDiagonalMatrixReader(int dimension);
    ~LowerRowDiagonalMatrixReader() = default;
    std::vector<int> readData(std::ifstream& file) const override;
};

class UpperColMatrixReader : public Reader {
public:
    UpperColMatrixReader(int dimension);
    ~UpperColMatrixReader() = default;
    std::vector<int> readData(std::ifstream& file) const override;
};

class LowerColMatrixReader : public Reader {
public:
    LowerColMatrixReader(int dimension);
    ~LowerColMatrixReader() = default;
    std::vector<int> readData(std::ifstream& file) const override;
};

class UpperColDiagonalMatrixReader : public Reader {
public:
    UpperColDiagonalMatrixReader(int dimension);
    ~UpperColDiagonalMatrixReader() = default;
    std::vector<int> readData(std::ifstream& file) const override;
};

class LowerColDiagonalMatrixReader : public Reader {
public:
    LowerColDiagonalMatrixReader(int dimension);
    ~LowerColDiagonalMatrixReader() = default;
    std::vector<int> readData(std::ifstream& file) const override;
};


FullMatrixReader::FullMatrixReader(int dimension) : Reader(dimension) {};
UpperRowMatrixReader::UpperRowMatrixReader(int dimension) : Reader(dimension) {};
LowerRowMatrixReader::LowerRowMatrixReader(int dimension) : Reader(dimension) {};
UpperRowDiagonalMatrixReader::UpperRowDiagonalMatrixReader(int dimension) : Reader(dimension) {};
LowerRowDiagonalMatrixReader::LowerRowDiagonalMatrixReader(int dimension) : Reader(dimension) {};
UpperColMatrixReader::UpperColMatrixReader(int dimension) : Reader(dimension) {};
LowerColMatrixReader::LowerColMatrixReader(int dimension) : Reader(dimension) {};
UpperColDiagonalMatrixReader::UpperColDiagonalMatrixReader(int dimension) : Reader(dimension) {};
LowerColDiagonalMatrixReader::LowerColDiagonalMatrixReader(int dimension) : Reader(dimension) {};

std::vector<int> FullMatrixReader::readData(std::ifstream& file) const {
    std::vector<int> data(dimension * dimension);

    for(int row = 0; row < dimension; ++row)
        for(int col = 0; col < dimension; ++col)
            file >> data[row * dimension + col];

    return data;
}

std::vector<int> UpperRowMatrixReader::readData(std::ifstream& file) const {
    std::vector<int> data(dimension * dimension);

    for(int row = 0; row < dimension - 1; ++row) {
        for(int col = row + 1; col < dimension; ++col){
            file >> data[row * dimension + col];
            data[col * dimension + row] = data[row * dimension + col];
        } 
    }
    return data;
}

std::vector<int> LowerRowMatrixReader::readData(std::ifstream& file) const {
    std::vector<int> data(dimension * dimension);

    for(int row = 1; row < dimension; ++row) {
        for(int col = 0; col < row; ++col){
            file >> data[row * dimension + col];
            data[col * dimension + row] = data[row * dimension + col];
        } 
    }
    return data;
}

std::vector<int> UpperRowDiagonalMatrixReader::readData(std::ifstream& file) const {
    std::vector<int> data(dimension * dimension);

    for(int row = 0; row < dimension; ++row) {
        for(int col = row; col < dimension; ++col){
            file >> data[row * dimension + col];
            data[col * dimension + row] = data[row * dimension + col];
        } 
    }
    return data;
}

std::vector<int> LowerRowDiagonalMatrixReader::readData(std::ifstream& file) const {
    std::vector<int> data(dimension * dimension);

    for(int row = 0; row < dimension; ++row) {
        for(int col = 0; col <= row; ++col){
            file >> data[row * dimension + col];
            data[col * dimension + row] = data[row * dimension + col];
        } 
    }
    return data;
}

std::vector<int> UpperColMatrixReader::readData(std::ifstream& file) const {
    std::vector<int> data(dimension * dimension);

    for(int col = 1; col < dimension; ++col) {
        for(int row = 0; row < col; ++row){
            file >> data[row * dimension + col];
            data[col * dimension + row] = data[row * dimension + col];
        } 
    }
    return data;
}

std::vector<int> LowerColMatrixReader::readData(std::ifstream& file) const {
    std::vector<int> data(dimension * dimension);

    for(int col = 0; col < dimension - 1; ++col) {
        for(int row = col + 1; row < dimension; ++row){
            file >> data[row * dimension + col];
            data[col * dimension + row] = data[row * dimension + col];
        } 
    }
    return data;
}

std::vector<int> UpperColDiagonalMatrixReader::readData(std::ifstream& file) const {
    std::vector<int> data(dimension * dimension);

    for(int col = 0; col < dimension; ++col) {
        for(int row = 0; row <= col; ++row){
            file >> data[row * dimension + col];
            data[col * dimension + row] = data[row * dimension + col];
        } 
    }
    return data;
}

std::vector<int> LowerColDiagonalMatrixReader::readData(std::ifstream& file) const {
    std::vector<int> data(dimension * dimension);

    for(int col = 0; col < dimension - 1; ++col) {
        for(int row = col; row < dimension; ++row){
            file >> data[row * dimension + col];
            data[col * dimension + row] = data[row * dimension + col];
        } 
    }
    return data;
}



#endif // __MATRIXREADERS_H__