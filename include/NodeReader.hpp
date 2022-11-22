#ifndef __NODEREADER_H__
#define __NODEREADER_H__

#include "Reader.hpp"

namespace {
    union Coord{
        struct {float x, y;};
        struct {float latitude, longitude;};
    };
}

class NodeReader : public Reader {
public:
    NodeReader(int dimension);
    ~NodeReader() = default;
    std::vector<int> readData(std::ifstream& file) const override;

protected:
    virtual int calcDistance(Coord i, Coord j) const = 0;
    std::vector<Coord> readCoords(std::ifstream& file) const;

};

NodeReader::NodeReader(int dimension) : Reader(dimension) {};

std::vector<int> NodeReader::readData(std::ifstream& file) const {
    
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

std::vector<Coord> NodeReader::readCoords(std::ifstream& file) const {
    
    int idx;
    std::vector<Coord> coords(dimension);

    for(int i = 0; i < dimension; i++) {
        file >> idx >> coords[i].x >> coords[i].y;
    }
    return coords;
}


#endif // __NODEREADER_H__