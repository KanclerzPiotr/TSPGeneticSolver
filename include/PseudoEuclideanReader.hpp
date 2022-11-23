#ifndef __PSEUDOEUCLIDEANREADER_H__
#define __PSEUDOEUCLIDEANREADER_H__

#include <cmath>
#include "NodeReader.hpp"

class PseudoEuclideanReader : public NodeReader {
public:
    PseudoEuclideanReader(int dimension);
    ~PseudoEuclideanReader() = default;

protected:
    int calcDistance(Coord i, Coord j) const override;

};

PseudoEuclideanReader::PseudoEuclideanReader(int dimension) : NodeReader(dimension) {};

int PseudoEuclideanReader::calcDistance(Coord i, Coord j) const {

    float x = i.x - j.x;
    float y = i.y - j.y;
    float rij = std::sqrt((x * x + y * y) / 10.0f);
    int tij = static_cast<int>( rij + 0.5f );
    return (tij < rij) ? tij + 1 : tij;
}

#endif // __PSEUDOEUCLIDEANREADER_H__