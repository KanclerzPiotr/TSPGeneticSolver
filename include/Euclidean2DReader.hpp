#ifndef __EUCLIDEAN2DREADER_H__
#define __EUCLIDEAN2DREADER_H__

#include <cmath>
#include "Reader.hpp"

namespace {
    struct Coord{
        float x, y;
    };
}


class Euclidean2DReader : public Reader {
public:
    Euclidean2DReader(int dimension);
    ~Euclidean2DReader() = default;
    std::vector<int> readData(std::ifstream& file) const override;

private:
    std::vector<Coord> readCoords(std::ifstream& file) const;
    int calcDistance(Coord i, Coord j) const;

};

Euclidean2DReader::Euclidean2DReader(int dimension) : Reader(dimension) {};

int Euclidean2DReader::calcDistance(Coord i, Coord j) const {

    float x = i.x - j.x;
    float y = i.y - j.y;
    float distance = std::sqrt(x * x + y * y);
    return static_cast<int>(distance + 0.5f);
}

std::vector<int> Euclidean2DReader::readData(std::ifstream& file) const {
    
    std::vector<int> data(dimension * dimension);
    auto coords = readCoords(file);

    for(int i = 0; i < dimension; ++i) {
        for(int j = i+1; j < dimension; ++j)
        {
            data[i * dimension + j] = calcDistance(coords[i], coords[j]);
            data[j * dimension + i] = data[i * dimension + j];
        }
    }
    return data;
}

std::vector<Coord> Euclidean2DReader::readCoords(std::ifstream& file) const {
    
    int idx;
    std::vector<Coord> coords(dimension);

    for(int i = 0; i < dimension; i++) {
        file >> idx >> coords[i].x >> coords[i].y;
    }
    return coords;
}

#endif // __EUCLIDEAN2DREADER_H__