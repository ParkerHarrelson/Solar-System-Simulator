
#ifndef SOLARSYSTEMMODEL_H
#define SOLARSYSTEMMODEL_H

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <celestial/CelestialBody.h>
#include <utils/PairDefinitions.h>

namespace SolarSystem {

	class SolarSystemModel {

	public:

		SolarSystemModel() = default;

		inline void addCelestialBody(std::unique_ptr<CelestialBody> celestialBody) {
			this->celestialBodies.push_back(std::move(celestialBody));
		}

		const std::vector<std::unique_ptr<CelestialBody>>& getCelestialBodies() const {
			return this->celestialBodies;
		}

		std::pair<int, double> getForceBetweenBodies(const CelestialBody* body1, const CelestialBody* body2) const;

		void removeCelestialBody(const std::string& name);

	private:

		std::vector<std::unique_ptr<CelestialBody>> celestialBodies;		// The storage of all of the celestial bodies that will be included in the simulation
		std::unordered_map<std::pair<const CelestialBody*, const CelestialBody*>, std::pair<int, double>, Utilities::PairHash, Utilities::PairEqual> forceCalculationMap;
	};
}

#endif