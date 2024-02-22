
#ifndef POSITION_H
#define POSITION_H

namespace Utilities {

	class Position {

	public:

		Position(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

		double getX() const {
			return this->x;
		}

		double getY() const {
			return this->y;
		}

		double getZ() const {
			return this->z;
		}

		void setX(double newXCoordinate) {
			this->x = newXCoordinate;
		}

		void setY(double newYCoordinate) {
			this->y = newYCoordinate;
		}

		void setZ(double newZCoordinate) {
			this->z = newZCoordinate;
		}

		double distanceToDifferentPosition(const Position& otherPosition) const;

		void translate(double dx, double dy, double dz);

	private:

		double x, y, z;
	};
}

#endif
