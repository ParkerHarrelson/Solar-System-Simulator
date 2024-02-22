
#ifndef STAR_H
#define STAR_H

#include<CelestialBody.h>
#include<utils/Position.h>

namespace SolarSystem {

	class Star : public CelestialBody {

		// Represents a Star which is a celestial body but has additional properties specific only to stars. Likely will only be used in this simulation
		// for the Sun, but have the ability to create any type of star we want

	public: 

		Star(double mass, double velocity, double radius, std::string name, Utilities::Position& position, double angularVelocity, double luminosity, double temperature)
			: CelestialBody(mass, velocity, radius, name, position, angularVelocity), luminosity(luminosity), temperature(temperature) {}

		virtual void updatePosition() override;

		inline double getLuminosity() const {
			return this->luminosity;
		}

		inline double getTemperature() const {
			return this->temperature;
		}

	private:

		const double luminosity;	// the luminosity of the Star in Watts
		const double temperature;	// the temperature of the Star in Kelvin
	};
}

#endif