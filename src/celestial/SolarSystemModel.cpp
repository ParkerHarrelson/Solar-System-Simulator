#include "SolarSystemModel.h"

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
