#ifndef VECTOR_H
#define VECTOR_H

#include<stdexcept>
#include<cmath>

namespace Utilities {

    class Vector {
    public:

        Vector(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

        Vector(const Vector& other) = default;

        Vector(Vector&& other) noexcept = default;

        ~Vector() = default;

        Vector& operator=(const Vector& other) = default;

        Vector& operator=(Vector&& other) noexcept = default;

        Vector operator+(const Vector& rhs) const {
            return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        Vector operator-(const Vector& rhs) const {
            return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
        }
        
        Vector operator*(double scalar) const {
            return Vector(x * scalar, y * scalar, z * scalar);
        }

        Vector operator/(double scalar) const {
            if (scalar == 0) throw std::runtime_error("Division by zero.");
            return Vector(x / scalar, y / scalar, z / scalar);
        }

        friend Vector operator*(double scalar, const Vector& vector) {
            return Vector(scalar * vector.x, scalar * vector.y, scalar * vector.z);
        }

        Vector& operator+=(const Vector& rhs);

        Vector& operator-=(const Vector& rhs);

        double dot(const Vector& rhs) const {
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }

        Vector normalize() const {
            double mag = magnitude();
            if (mag == 0) throw std::runtime_error("Attempt to normalize a zero vector.");
            return *this / mag;
        }

        double magnitude() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        Vector cross(const Vector& rhs) const;

        double distanceTo(const Vector& other) const;

        void translate(double dx, double dy, double dz);

        double getX() const { return x; }
        double getY() const { return y; }
        double getZ() const { return z; }


        void setX(double newX) { x = newX; }
        void setY(double newY) { y = newY; }
        void setZ(double newZ) { z = newZ; }

    private:
        double x, y, z;
    };

} 

#endif 
