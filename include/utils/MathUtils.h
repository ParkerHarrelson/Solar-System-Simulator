
#ifndef MATHUTILS_H
#define MATHUTILS_H

namespace Utilities {

	class MathUtils {

	public:

		static constexpr double convertTemperatureToFahrenheitFromKelvin(double temperatureInKelvin) {
			return (temperatureInKelvin - 273.15) * 9 / 5 + 32;
		}

		static constexpr double convertTemperatureToCelsiusFromKelvin(double temperatureInKelvin) {
			return temperatureInKelvin - 273.15;
		}

	};
}

#endif