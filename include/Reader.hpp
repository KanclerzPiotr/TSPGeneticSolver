#ifndef __READER_H__
#define __READER_H__

#include <vector>
#include <fstream>

class Reader {

protected:
    int dimension;

public: 
    Reader(int dimension);
    virtual std::vector<int> readData(std::ifstream& file) const = 0;
    virtual ~Reader() = default;

};

Reader::Reader(int dimension) : dimension(dimension) {}

#endif // __READER_H__