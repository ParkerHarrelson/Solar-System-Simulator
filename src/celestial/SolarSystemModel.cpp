#include "SolarSystemModel.h"
#include <optional>

using namespace SolarSystem;

void SolarSystemModel::removeCelestialBody(const std::string& name) {
    auto it = std::find_if(celestialBodies.begin(), celestialBodies.end(),
        [&name](const std::unique_ptr<CelestialBody>& body) {
            return body->getCelestialBodyName() == name;
        });

    if (it != celestialBodies.end()) {
        celestialBodies.erase(it);
    }
}

std::pair<int, double> SolarSystemModel::getForceBetweenBodies(const CelestialBody* body1, const CelestialBody* body2) const {
    std::pair<const SolarSystem::CelestialBody*, const SolarSystem::CelestialBody*> key = { body1, body2 };

    auto it = forceCalculationMap.find(key);

    if (it != forceCalculationMap.end()) {
        return it->second;
    }

    return std::make_pair(-1, 0.0);
}