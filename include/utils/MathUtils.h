
#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <utils/UtilitiesNamespace.h>
#include <celestial/CelestialBody.h>

namespace Utilities {

	class MathUtils {

	public:

		static constexpr double convertTemperatureToFahrenheitFromKelvin(double temperatureInKelvin) {
			return (temperatureInKelvin - 273.15) * 9 / 5 + 32;
		}

		static constexpr double convertTemperatureToCelsiusFromKelvin(double temperatureInKelvin) {
			return temperatureInKelvin - 273.15;
		}

		static constexpr double convertRotationalPeriodToAngularVelocity(double rotationalPeriod) {
			return (2 * PI) / rotationalPeriod;
		}

		static constexpr double convertAngularVelocityToRotationalPeriod(double angularVelocity) {
			return (2 * PI) / angularVelocity;
		}

		static Vector calculateGravitationalForceBetweenMasses(const SolarSystem::CelestialBody& bodyOne, const SolarSystem::CelestialBody& bodyTwo);

	};
}

#endif