#include "utils/MathUtils.h"
#include "celestial/CelestialBody.h" 

using namespace Utilities;

double MathUtils::calculateGravitationalForceBetweenMasses(const SolarSystem::CelestialBody& bodyOne, const SolarSystem::CelestialBody& bodyTwo) {
    const Utilities::Position& bodyOnePosition = bodyOne.getCurrentPosition();
    const Utilities::Position& bodyTwoPosition = bodyTwo.getCurrentPosition();

    double euclideanDistance = bodyOnePosition.distanceToDifferentPosition(bodyTwoPosition);

    return GRAVITATIONAL_CONSTANT * ((bodyOne.getMass() * bodyTwo.getMass()) / (euclideanDistance * euclideanDistance));
}

// 5,890,329,911 == 100 // Mercury and Pluto
// 37,236,121,041,383 == 90 // earth and titan
// 49,960,826,401,321,459 == 50// pluto and sun
// 35,426,928,201,758,164,374,160 == 10 // earth and sun

// map where the key is the pair of the two objects (earth and sun for example)
// value for the key is a Pair of Integer and Double
// The integer is the Score and Double is the last calculated Force
// each frame we will iterate the map and get each key and get the Pair Value from it.
// if the integer value == 0 then recalculate the force for that pair and then based on that force calculate
// the new position and then set a new value for that key based on that force
// if the integer value != 0 then decrement the value and then grab the already existing force and use some sort linear interpolation to approximate correct position