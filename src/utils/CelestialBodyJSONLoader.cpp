
#include <utils/CelestialBodyJSONLoader.h>
using namespace Utilities;
using json = nlohmann::json;

std::vector<std::unique_ptr<SolarSystem::CelestialBody>> CelestialBodyJSONLoader::LoadBodies(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filepath);
    }

    json j;
    file >> j;

    std::vector<std::unique_ptr<SolarSystem::CelestialBody>> bodies;

    for (const auto& item : j["celestialBodies"]) {
        std::string type = item["type"];
        if (type == "Star") {
            bodies.push_back(std::make_unique<SolarSystem::Star>(
                item["mass"],
                Utilities::Vector(item["position"]["x"], item["position"]["y"], item["position"]["z"]),
                item["radius"],
                item["name"],
                Utilities::Vector(item["velocity"]["x"], item["velocity"]["y"], item["velocity"]["z"]),
                item["angularVelocity"],
                item["luminosity"],
                item["surfaceTemperature"]
            ));
        }
        else if (type == "Planet") {
            
        }
       
    }

    return bodies;
}
