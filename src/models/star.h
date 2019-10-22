#ifndef _STAR_H
#define _STAR_H

#include "../utils/coordinate.h"
#include <cmath>

static size_t count = 0;

class Star
{
public:
    Star() = delete;
    Star(const size_t galaxyClass, const double mass, const Coordinate& coord, const Coordinate& dir)
        : id{++count}, galaxyClass{galaxyClass}, mass{mass}, coord{coord}, dir{dir} {};
    ~Star() = default;

    bool operator==(const Star& other) {return id == other.id;}

    size_t getId() const {return id;}
    double getMass() const {return mass;}
    Coordinate getCoord() const {return coord;}
    Coordinate getDir() const {return dir;}

    void setCoord(const Coordinate& coord) {this->coord = coord;}
    void setDir(const Coordinate& dir) {this->dir = dir;}

    const std::string exportString() const;
    void showStar() const;
    void printCenterOfMassWith(const Star &other);

private:
    size_t id;
    size_t galaxyClass;
    double mass;
    Coordinate coord;
    Coordinate dir; // Same Coordinate structure can used for direction too
};

#endif // _STAR_H