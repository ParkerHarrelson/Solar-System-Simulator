
#include <utils/Vector.h>

using namespace Utilities;

double Vector::distanceTo(const Vector& otherPosition) const {
    return std::sqrt(
        (x - otherPosition.x) * (x - otherPosition.x) +
        (y - otherPosition.y) * (y - otherPosition.y) +
        (z - otherPosition.z) * (z - otherPosition.z)
    );
}

void Vector::translate(double dx, double dy, double dz) {
    x += dx;
    y += dy;
    z += dz;
}

Vector Vector::cross(const Vector& rhs) const {
    return Vector(
        y * rhs.z - z * rhs.y, 
        z * rhs.x - x * rhs.z, 
        x * rhs.y - y * rhs.x  
    );
}

Vector& Vector::operator+=(const Vector& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector& Vector::operator-=(const Vector& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}