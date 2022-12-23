#ifndef __EXPLICITREADERFACTORY_H__
#define __EXPLICITREADERFACTORY_H__

#include "TSPSpecification.hpp"
#include "MatrixReaders.hpp"


class ExplicitReaderFactory {
public:
    static std::unique_ptr<Reader> makeReader(int dimension, const TSPProblem::EDGE_WEIGHT_FORMAT format)
    {
        using namespace TSPProblem;
        switch (format)
        {
        case EDGE_WEIGHT_FORMAT::FULL_MATRIX:
            return std::make_unique<FullMatrixReader>(dimension);
        case EDGE_WEIGHT_FORMAT::UPPER_ROW:
            return std::make_unique<UpperRowMatrixReader>(dimension);
        case EDGE_WEIGHT_FORMAT::LOWER_ROW:
            return std::make_unique<LowerRowMatrixReader>(dimension);
        case EDGE_WEIGHT_FORMAT::UPPER_DIAG_ROW:
            return std::make_unique<UpperRowDiagonalMatrixReader>(dimension);
        case EDGE_WEIGHT_FORMAT::LOWER_DIAG_ROW:
            return std::make_unique<LowerRowDiagonalMatrixReader>(dimension);
        case EDGE_WEIGHT_FORMAT::UPPER_COL:
            return std::make_unique<UpperColMatrixReader>(dimension);
        case EDGE_WEIGHT_FORMAT::LOWER_COL:
            return std::make_unique<LowerColMatrixReader>(dimension);
        case EDGE_WEIGHT_FORMAT::UPPER_DIAG_COL:
            return std::make_unique<UpperColDiagonalMatrixReader>(dimension);
        case EDGE_WEIGHT_FORMAT::LOWER_DIAG_COL:
            return std::make_unique<LowerColDiagonalMatrixReader>(dimension);
        default:
            throw std::invalid_argument("Unknown EDGE_WEIGHT_FORMAT ");
        }
    }

};


#endif // __EXPLICITREADERFACTORY_H__