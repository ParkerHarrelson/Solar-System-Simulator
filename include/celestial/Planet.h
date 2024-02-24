
#ifndef PLANET_H
#define PLANET_H

#include <celestial/CelestialBody.h>

namespace SolarSystem {

	class Planet : public CelestialBody {

	public:

		Planet(double mass, const Utilities::Vector& velocity, double radius, std::string name, const Utilities::Vector& position, double angularVelocity)
			: CelestialBody(mass, velocity, radius, name, position, angularVelocity) {}

		//void draw(GLuint shaderProgram) override;

	};
}

#endif 
