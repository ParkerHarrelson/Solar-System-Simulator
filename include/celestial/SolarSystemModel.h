
#ifndef SOLARSYSTEMMODEL_H
#define SOLARSYSTEMMODEL_H

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <celestial/CelestialBody.h>

namespace SolarSystem {

	class SolarSystemModel {

	public:

		inline void addCelestialBody(std::unique_ptr<CelestialBody> celestialBody) {
			this->celestialBodies.push_back(std::move(celestialBody));
		}

		const std::vector<std::unique_ptr<CelestialBody>>& getCelestialBodies() const {
			return this->celestialBodies;
		}

		void removeCelestialBody(const std::string& name);

	private:

		std::vector<std::unique_ptr<CelestialBody>> celestialBodies;		// The storage of all of the celestial bodies that will be included in the simulation
	};
}

#endif