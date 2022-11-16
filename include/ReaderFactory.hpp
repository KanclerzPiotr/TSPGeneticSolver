#ifndef __READERFACTORY_H__
#define __READERFACTORY_H__

#include "TSPSpecification.hpp"
#include "ExplicitReaderFactory.hpp"
#include "Reader.hpp"

class ReaderFactory {

public:
    static Reader* makeReader(int dimension, const TSPProblem::EDGE_WEIGHT_TYPE type, const TSPProblem::EDGE_WEIGHT_FORMAT format)
    {
        using namespace TSPProblem;
        switch (type)
        {
        case EDGE_WEIGHT_TYPE::EXPLICIT:
            return ExplicitReaderFactory::makeReader(dimension, format);
        default:
            break;
        }
    }

};


#endif // __READERFACTORY_H__