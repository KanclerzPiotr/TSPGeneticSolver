#ifndef __READERFACTORY_H__
#define __READERFACTORY_H__

#include "TSPSpecification.hpp"
#include "ExplicitReaderFactory.hpp"
#include "Euclidean2DReader.hpp"
#include "GeographicalReader.hpp"
#include "PseudoEuclideanReader.hpp"

class ReaderFactory {

public:
    static std::unique_ptr<Reader> makeReader(int dimension, const TSPProblem::EDGE_WEIGHT_TYPE type, const TSPProblem::EDGE_WEIGHT_FORMAT format)
    {
        using namespace TSPProblem;
        switch (type)
        {
        case EDGE_WEIGHT_TYPE::EXPLICIT:
            return ExplicitReaderFactory::makeReader(dimension, format);
        case EDGE_WEIGHT_TYPE::EUC_2D:
            return std::make_unique<Euclidean2DReader>(dimension);
        case EDGE_WEIGHT_TYPE::GEO:
            return std::make_unique<GeographicalReader>(dimension);
        case EDGE_WEIGHT_TYPE::ATT:
            return std::make_unique<PseudoEuclideanReader>(dimension);
        default:
            throw std::invalid_argument("Unknown EDGE_WEIGHT_TYPE");
        }
    }

};


#endif // __READERFACTORY_H__