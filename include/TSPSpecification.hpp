#ifndef __TSPSPECIFICATION_H__
#define __TSPSPECIFICATION_H__

#include <map>
#include <string>

namespace TSPProblem
{

    enum class SPECIFICATION {
        NAME,
        TYPE,
        COMMENT,
        DIMENSION,
        CAPACITY,
        EDGE_WEIGHT_TYPE,
        EDGE_WEIGHT_FORMAT,
        EDGE_DATA_FORMAT,
        NODE_COORD_TYPE,
        DISPLAY_DATA_TYPE,
        NODE_COORD_SECTION,
        DEPOT_SECTION,
        DEMAND_SECTION,
        EDGE_DATA_SECTION,
        FIXED_EDGES_SECTION,
        DISPLAY_DATA_SECTION,
        TOUR_SECTION,
        EDGE_WEIGHT_SECTION,
        END_OF_FILE
    };

    static std::map<std::string, SPECIFICATION> specificationStrToEnum{
        {"NAME", SPECIFICATION::NAME},
        {"TYPE", SPECIFICATION::TYPE},
        {"COMMENT", SPECIFICATION::COMMENT},
        {"DIMENSION", SPECIFICATION::DIMENSION},
        {"CAPACITY", SPECIFICATION::CAPACITY},
        {"EDGE_WEIGHT_TYPE", SPECIFICATION::EDGE_WEIGHT_TYPE},
        {"EDGE_WEIGHT_FORMAT", SPECIFICATION::EDGE_WEIGHT_FORMAT},
        {"EDGE_DATA_FORMAT", SPECIFICATION::EDGE_DATA_FORMAT},
        {"NODE_COORD_TYPE", SPECIFICATION::NODE_COORD_TYPE},
        {"DISPLAY_DATA_TYPE", SPECIFICATION::DISPLAY_DATA_TYPE},
        {"NODE_COORD_SECTION", SPECIFICATION::NODE_COORD_SECTION},
        {"DEPOT_SECTION", SPECIFICATION::DEPOT_SECTION},
        {"DEMAND_SECTION", SPECIFICATION::DEMAND_SECTION},
        {"EDGE_DATA_SECTION", SPECIFICATION::EDGE_DATA_SECTION},
        {"FIXED_EDGES_SECTION", SPECIFICATION::FIXED_EDGES_SECTION},
        {"DISPLAY_DATA_SECTION", SPECIFICATION::DISPLAY_DATA_SECTION},
        {"TOUR_SECTION", SPECIFICATION::TOUR_SECTION},
        {"EDGE_WEIGHT_SECTION", SPECIFICATION::EDGE_WEIGHT_SECTION},
        {"EOF", SPECIFICATION::END_OF_FILE}
    };

    enum class TYPE {
        TSP,
        ATSP,
        SOP,
        HCP,
        CVRP,
        TOUR,
    };

    static std::map<std::string, TYPE> typeStrToEnum{
        {"TSP", TYPE::TSP},
        {"ATSP", TYPE::ATSP},
        {"SOP", TYPE::SOP},
        {"HCP", TYPE::HCP},
        {"CVRP", TYPE::CVRP},
        {"TOUR", TYPE::TOUR}
    };

    enum class EDGE_WEIGHT_TYPE {
        EXPLICIT, 
        EUC_2D,
        EUC_3D,
        MAX_2D,
        MAX_3D,
        MAN_2D,
        MAN_3D,
        CEIL_2D,
        GEO,
        ATT,
        XRAY1,
        XRAY2,
        SPECIAL,
    };

    static std::map<std::string, EDGE_WEIGHT_TYPE> edgeWeightTypeStrToEnum{
        {"EXPLICIT", EDGE_WEIGHT_TYPE::EXPLICIT},
        {"EUC_2D", EDGE_WEIGHT_TYPE::EUC_2D},
        {"EUC_3D", EDGE_WEIGHT_TYPE::EUC_3D},
        {"MAX_2D", EDGE_WEIGHT_TYPE::MAX_2D},
        {"MAX_3D", EDGE_WEIGHT_TYPE::MAX_3D},
        {"MAN_2D", EDGE_WEIGHT_TYPE::MAN_2D},
        {"MAN_3D", EDGE_WEIGHT_TYPE::MAN_3D},
        {"CEIL_2D",EDGE_WEIGHT_TYPE::CEIL_2D},
        {"GEO", EDGE_WEIGHT_TYPE::GEO},
        {"ATT", EDGE_WEIGHT_TYPE::ATT},
        {"XRAY1", EDGE_WEIGHT_TYPE::XRAY1},
        {"XRAY2", EDGE_WEIGHT_TYPE::XRAY2},
        {"SPECIAL", EDGE_WEIGHT_TYPE::SPECIAL}
    };

    enum class EDGE_WEIGHT_FORMAT {
        FUNCTION,
        FULL_MATRIX,
        UPPER_ROW,
        LOWER_ROW,
        UPPER_DIAG_ROW,
        LOWER_DIAG_ROW,
        UPPER_COL,
        LOWER_COL,
        UPPER_DIAG_COL,
        LOWER_DIAG_COL
    };

    static std::map<std::string, EDGE_WEIGHT_FORMAT> edgeWeightFormatStrToEnum {
        {"FUNCTION", EDGE_WEIGHT_FORMAT::FUNCTION},
        {"FULL_MATRIX", EDGE_WEIGHT_FORMAT::FULL_MATRIX},
        {"UPPER_ROW", EDGE_WEIGHT_FORMAT::UPPER_ROW},
        {"LOWER_ROW", EDGE_WEIGHT_FORMAT::LOWER_ROW},
        {"UPPER_DIAG_ROW", EDGE_WEIGHT_FORMAT::UPPER_DIAG_ROW},
        {"LOWER_DIAG_ROW", EDGE_WEIGHT_FORMAT::LOWER_DIAG_ROW},
        {"UPPER_COL", EDGE_WEIGHT_FORMAT::UPPER_COL},
        {"LOWER_COL", EDGE_WEIGHT_FORMAT::LOWER_COL},
        {"UPPER_DIAG_COL", EDGE_WEIGHT_FORMAT::UPPER_DIAG_COL},
        {"LOWER_DIAG_COL", EDGE_WEIGHT_FORMAT::LOWER_DIAG_COL}
    };

    enum class EDGE_DATA_FORMAT {
        EDGE_LIST,
        ADJ_LIST
    };

    enum class NODE_COORD_TYPE {
        TWOD_COORDS,
        THREED_COORDS,
        NO_CORDS,
    };

    enum class DISPLAY_DATA_TYPE {
        COORD_DISPLAY,
        TWOD_DISPLAY,
        NO_DISPLAY
    };

} // namespace TSPProblem

#endif // __TSPSPECIFICATION_H__