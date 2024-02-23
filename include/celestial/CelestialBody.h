
#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <string>
#include<utils/Vector.h>

namespace SolarSystem {

	class CelestialBody {

		// Represents a generic celestial body within the solar system.
		// This class serves as a base for more specific types of celestial bodies, such as planets, stars, and moons.

	public:
		
		CelestialBody(double mass, const Utilities::Vector& velocity, double radius, std::string name, const Utilities::Vector& position, double angularVelocity)  
			: mass(mass), velocity(velocity), radius(radius), name(std::move(name)), currentPosition(position), angularVelocity(angularVelocity) {}

		inline double getMass() const {
			return this->mass;
		}

		inline double getRadius() const {
			return this->radius;
		}

		inline Utilities::Vector getVelocity() const {
			return this->velocity;
		}

		inline std::string getCelestialBodyName() const {
			return this->name;
		}

		inline const Utilities::Vector& getCurrentPosition() const {
			return this->currentPosition;
		}

		inline double getAngularVelocity() const {
			return this->angularVelocity;
		}

		inline void setVelocity(const Utilities::Vector& velocity) {
			this->velocity = velocity;
		}

		inline void setPosition(const Utilities::Vector& newPosition) {
			this->currentPosition = newPosition;
		}

		inline void setAngularVelocity(double omega) {
			this->angularVelocity = omega;
		}

		virtual void updatePosition() = 0;

		virtual ~CelestialBody() = default;

	private:

		const double mass;						// Mass of the celestial body in Kilograms(kg)
		const double radius;					// Radius of the celestial body in Kilometers (km)
		const std::string name;					// Name of the celestial body
		Utilities::Vector currentPosition;		// The current position of the celestial body as a vector
		Utilities::Vector velocity;				// Vector velocity of the body
		double angularVelocity;					// The angular velocity of the celestial body

	};
}

#endif