#ifndef __GEOGRAPHICALREADER_H__
#define __GEOGRAPHICALREADER_H__

#include <cmath>
#include "NodeReader.hpp"

class GeographicalReader : public NodeReader {
public:
    GeographicalReader(int dimension);
    ~GeographicalReader() = default;

protected:
    Coord getGeographicalCoord(Coord x) const;
    int calcDistance(Coord i, Coord j) const override;
    const float PI = 3.141592;
    const float RRR = 6378.388;

};

GeographicalReader::GeographicalReader(int dimension) : NodeReader(dimension) {};

Coord GeographicalReader::getGeographicalCoord(Coord coord) const {
    int degx = static_cast<int>( coord.x + 0.5f);
    float minx = coord.x - degx;
    float latitude = PI * (degx + 5.0f * minx / 3.0f) / 180.0f;
    int degy = static_cast<int>( coord.y + 0.5f);
    float miny = coord.y - degy;
    float longitude = PI * (degy + 5.0f * miny / 3.0f) / 180.0f;
    return Coord{latitude, longitude};
}

int GeographicalReader::calcDistance(Coord i, Coord j)  const {
    
    Coord a = getGeographicalCoord(i);
    Coord b = getGeographicalCoord(j);
    float q1 = std::cos(a.longitude - b.longitude);
    float q2 = std::cos(a.latitude - b.latitude);
    float q3 = std::cos(a.latitude + b.latitude);

    return static_cast<int>( RRR * std::acos( 0.5f * ((1.0f + q1) * q2 - (1.0f - q1) * q3)) + 1.0f);
}

#endif // __GEOGRAPHICALREADER_H__