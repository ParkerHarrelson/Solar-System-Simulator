
#include<utils/Position.h>
#include<cmath>

using namespace Utilities;

double Position::distanceToDifferentPosition(const Position& otherPosition) const {
	return std::sqrt(
        (x - otherPosition.x) * (x - otherPosition.x) +
        (y - otherPosition.y) * (y - otherPosition.y) +
        (z - otherPosition.z) * (z - otherPosition.z)
    );
}

void Position::translate(double dx, double dy, double dz) {
    x += dx;
    y += dy;
    z += dz;
}