
#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <string>
#include<utils/Position.h>

namespace SolarSystem {

	class CelestialBody {

		// Represents a generic celestial body within the solar system.
		// This class serves as a base for more specific types of celestial bodies, such as planets, stars, and moons.

	public:
		
		CelestialBody(double mass, double velocity, double radius, std::string name, const Utilities::Position& position, double angularVelocity)  
			: mass(mass), velocity(velocity), radius(radius), name(std::move(name)), currentPosition(position), angularVelocity(angularVelocity) {}

		inline double getMass() const {
			return this->mass;
		}

		inline double getRadius() const {
			return this->radius;
		}

		inline double getVelocity() const {
			return this->velocity;
		}

		inline std::string getCelestialBodyName() const {
			return this->name;
		}

		inline const Utilities::Position& getCurrentPosition() const {
			return this->currentPosition;
		}

		inline double getAngularVelocity() const {
			return this->angularVelocity;
		}

		inline void setVelocity(double velocity) {
			this->velocity = velocity;
		}

		inline void setPosition(const Utilities::Position& newPosition) {
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
		Utilities::Position currentPosition;	// The current position of the celestial body in cartesian space at the center of the body
		double velocity;						// Instant time velocity of the celestial body in Kilometers / Second (km/s)
		double angularVelocity;					// The angular velocity of the celestial body

	};
}

#endif