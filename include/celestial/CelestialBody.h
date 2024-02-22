
#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <string>

namespace SolarSystem {

	class CelestialBody {

		// Represents a generic celestial body within the solar system.
		// This class serves as a base for more specific types of celestial bodies, such as planets, stars, and moons.

	public:
		
		CelestialBody(double mass, double velocity, double radius, std::string name) : mass(mass), velocity(velocity), radius(radius), name(std::move(name)) {}

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

		inline void setVelocity(double velocity) {
			this->velocity = velocity;
		}

		virtual void updatePosition() = 0;

		virtual ~CelestialBody() = default;

	private:

		const double mass;				// Mass of the celestial body in Kilograms(kg)
		const double radius;			// Radius of the celestial body in Kilometers (km)
		const std::string name;			// Name of the celestial body
		double velocity;				// Instant time velocity of the celestial body in Kilometers / Second (km/s)

	};
}

#endif