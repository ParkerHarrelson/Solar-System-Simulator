#include "utils/MathUtils.h"
#include "celestial/CelestialBody.h" 

using namespace Utilities;


Vector MathUtils::calculateGravitationalForceBetweenMasses(const SolarSystem::CelestialBody& bodyOne, const SolarSystem::CelestialBody& bodyTwo) {
    const Vector& positionOne = bodyOne.getCurrentPosition();
    const Vector& positionTwo = bodyTwo.getCurrentPosition();

    Vector direction = positionTwo - positionOne;

    double distance = direction.magnitude();

    if (distance == 0) {
        throw std::runtime_error("Attempt to calculate gravitational force between overlapping celestial bodies.");
    }

    double forceMagnitude = GRAVITATIONAL_CONSTANT_KM * (bodyOne.getMass() * bodyTwo.getMass()) / (distance * distance);

    Vector forceVector = direction.normalize() * forceMagnitude;

    return forceVector;
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