
#ifndef CELESTIALBODYJSONLOADER_H
#define CELESTIALBODYJSONLOADER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <utils/json.hpp>
#include <celestial/CelestialBody.h>
#include <celestial/Star.h>
#include <celestial/Planet.h>

namespace Utilities {

	class CelestialBodyJSONLoader {

	public:

		static std::vector<std::unique_ptr<SolarSystem::CelestialBody>> LoadBodies(const std::string& resourcePath);
	};
}

#endif