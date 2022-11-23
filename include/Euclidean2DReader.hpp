#ifndef __EUCLIDEAN2DREADER_H__
#define __EUCLIDEAN2DREADER_H__

#include <cmath>
#include "NodeReader.hpp"

class Euclidean2DReader : public NodeReader {
public:
    Euclidean2DReader(int dimension);
    ~Euclidean2DReader() = default;

protected:
    int calcDistance(Coord i, Coord j) const override;

};

Euclidean2DReader::Euclidean2DReader(int dimension) : NodeReader(dimension) {};

int Euclidean2DReader::calcDistance(Coord i, Coord j) const {

    float x = i.x - j.x;
    float y = i.y - j.y;
    float distance = std::sqrt(x * x + y * y);
    return static_cast<int>(distance + 0.5f);
}

#endif // __EUCLIDEAN2DREADER_H__