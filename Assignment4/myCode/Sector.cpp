#include <valarray>
#include "Sector.h"
#include <cmath>
#include <iostream>

// Constructor implementation

Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED) {
    // TODO: Calculate the distance to the Earth, and generate the sector code
    distance_from_earth = sqrt(x*x+y*y+z*z);
    int num = (int)distance_from_earth;
    std::string RL;
    std::string UD;
    std::string FB;

    if(x > 0)
        RL = "R";
    else if (x<0)
        RL = "L";
    else
        RL = "S";

    if(y > 0)
        UD = "U";
    else if (y<0)
        UD = "D";
    else
        UD = "S";

    if(z > 0)
        FB = "F";
    else if (z<0)
        FB = "B";
    else
        FB = "S";

    sector_code = std::to_string(num) + RL + UD + FB;

}

Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary
}

Sector& Sector::operator=(const Sector& other) {
    // TODO: Overload the assignment operator
    x = other.x;
    y = other.y;
    z = other.z;
    left = other.left;
    right = other.right;
    parent = other.parent;
    color = other.color;
    distance_from_earth = other.distance_from_earth;
    sector_code = other.sector_code;
    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}