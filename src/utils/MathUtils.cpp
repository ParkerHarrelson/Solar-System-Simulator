#include "utils/MathUtils.h"
#include "celestial/CelestialBody.h" 

using namespace Utilities;

double MathUtils::calculateGravitationalForceBetweenMasses(const SolarSystem::CelestialBody& bodyOne, const SolarSystem::CelestialBody& bodyTwo) {
    const Utilities::Position& bodyOnePosition = bodyOne.getCurrentPosition();
    const Utilities::Position& bodyTwoPosition = bodyTwo.getCurrentPosition();

    double euclideanDistance = bodyOnePosition.distanceToDifferentPosition(bodyTwoPosition);

    return GRAVITATIONAL_CONSTANT * ((bodyOne.getMass() * bodyTwo.getMass()) / (euclideanDistance * euclideanDistance));
}
