#ifndef __EXPLICITREADERFACTORY_H__
#define __EXPLICITREADERFACTORY_H__

#include "TSPSpecification.hpp"
#include "MatrixReaders.hpp"


class ExplicitReaderFactory {

public:
    static Reader* makeReader(int dimension, const TSPProblem::EDGE_WEIGHT_FORMAT format)
    {
        using namespace TSPProblem;
        switch (format)
        {
        case EDGE_WEIGHT_FORMAT::FULL_MATRIX:
            return new FullMatrixReader(dimension);
        case EDGE_WEIGHT_FORMAT::UPPER_ROW:
        case EDGE_WEIGHT_FORMAT::LOWER_ROW:
        case EDGE_WEIGHT_FORMAT::UPPER_DIAG_ROW:
        case EDGE_WEIGHT_FORMAT::LOWER_DIAG_ROW:
        case EDGE_WEIGHT_FORMAT::UPPER_COL:
        case EDGE_WEIGHT_FORMAT::LOWER_COL:
        case EDGE_WEIGHT_FORMAT::UPPER_DIAG_COL:
        case EDGE_WEIGHT_FORMAT::LOWER_DIAG_COL:
            break;
            
        default:
            break;
        }
    }

};


#endif // __EXPLICITREADERFACTORY_H__