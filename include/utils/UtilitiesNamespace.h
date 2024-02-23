#ifndef UTILITIESNAMESPACE_H
#define UTILITIESNAMESPACE_H

namespace Utilities {

    // Mathematical constants
    constexpr double PI = 3.14159265358979323846;
    constexpr double GRAVITATIONAL_CONSTANT = 6.67430e-11; // in m^3 kg^-1 s^-2

    // Conversion factors
    constexpr double KILOMETERS_PER_ASTRONOMICAL_UNIT = 1.496e+8; // Distance from Earth to the Sun in kilometers
    constexpr double SECONDS_PER_DAY = 86400;

    // generic utils functions
    template<typename T>
    const T& clamp(const T& v, const T& lo, const T& hi) {
        assert(!(hi < lo));
        return (v < lo) ? lo : (hi < v) ? hi : v;
    }
}

#endif 
