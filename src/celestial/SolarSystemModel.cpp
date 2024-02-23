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

std::pair<int, Utilities::Vector> SolarSystemModel::getForceBetweenBodies(const CelestialBody* body1, const CelestialBody* body2) const {
    std::pair<const SolarSystem::CelestialBody*, const SolarSystem::CelestialBody*> key = { body1, body2 };

    auto it = forceCalculationMap.find(key);

    if (it != forceCalculationMap.end()) {
        return it->second;
    }

    return std::make_pair(-1, 0.0);
}

int SolarSystemModel::determineNewScore(const Utilities::Vector& force, float timestep) {
    double forceMagnitude = force.magnitude();
    // Logarithm of force magnitude to compress the range
    double logForceMagnitude = std::log10(forceMagnitude + 1.0);

    // Normalize the log magnitude based on the expected range of forces
    const double logBase = 10; // Subtracting this to normalize our lowest meaningful log magnitude to around 0
    double normalizedLogMagnitude = logForceMagnitude - logBase;

    const int minScore = 1; // Minimum score for recalculations
    const int maxScore = 100; // Maximum score to prevent delays

    double scoreRange = maxScore - minScore;
    int score = maxScore - static_cast<int>((normalizedLogMagnitude / (25 - logBase)) * scoreRange * timestep);

    // Clamp the score within the defined min and max values
    return Utilities::clamp(score, minScore, maxScore);
}


int SolarSystemModel::adjustScoreBasedOnTimestep(int currentScore, float timestep, float fps) {
    const float idealTimestep = 1.0f / fps;

    float adjustmentFactor = timestep / idealTimestep;
    
    int adjustedScore = static_cast<int>(currentScore - adjustmentFactor);

    return std::max(adjustedScore, 0); 
}


/// <summary>
/// 
/// This method is where the balance of accuracy and performance happens
/// In this method we loop through all of the possible pairs in the existing system
/// and either calculate the force between the two bodies or use linear interpolation
/// to guess at what it should be. We base this decision off of the score during this
/// frame and the timestep
/// 
/// </summary>

void SolarSystemModel::processForceCalculationForPair(
    const std::pair<const CelestialBody*, const CelestialBody*>& pair,
    int& score,
    Utilities::Vector& force,
    float timestep,
    float fps) {

    if (score <= 0) {
        force = Utilities::MathUtils::calculateGravitationalForceBetweenMasses(*pair.first, *pair.second);
        score = determineNewScore(force, timestep);
    }
    else {
        score -= adjustScoreBasedOnTimestep(score, timestep, fps); 
    }
}

void SolarSystemModel::calculateForceVectorsBasedOnTimestep(float timestep, float fps) {
    for (auto& entry : forceCalculationMap) {
        auto& pair = entry.first;
        auto& scoreAndForce = entry.second;
        processForceCalculationForPair(pair, scoreAndForce.first, scoreAndForce.second, timestep, fps);
    }
}


void SolarSystemModel::calculateForceVectorsBasedOnTimestepParrallelized(float timestep, float fps) {
    unsigned int numThreads = std::thread::hardware_concurrency();
    auto totalEntries = forceCalculationMap.size();
    auto entriesPerThread = static_cast<size_t>(std::ceil(totalEntries / static_cast<double>(numThreads)));

    std::vector<std::thread> threads;
    auto it = forceCalculationMap.begin();

    for (unsigned int i = 0; i < numThreads && it != forceCalculationMap.end(); ++i) {
        threads.emplace_back([&, i, this, timestep] {
            auto start = std::next(it, i * entriesPerThread);
            auto end = (static_cast<unsigned long long>(i) + 1) * entriesPerThread > totalEntries ? forceCalculationMap.end() : std::next(start, entriesPerThread);
            for (auto &it = start; it != end && it != forceCalculationMap.end(); ++it) {
                processForceCalculationForPair(it->first, it->second.first, it->second.second, timestep, fps);
            }
            });
    }

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}


void SolarSystemModel::calculateTotalForces() {
    netForces.clear();
    for (const auto& bodyPtr : celestialBodies) {
        netForces[bodyPtr.get()] = Utilities::Vector(0, 0, 0);
    }

    for (const auto& entry : forceCalculationMap) {
        const auto& bodyPair = entry.first;
        const auto& forceInfo = entry.second;
        const auto& forceVector = forceInfo.second;

        netForces[bodyPair.first] -= forceVector;

        netForces[bodyPair.second] += forceVector;
    }
}

void SolarSystemModel::updateCelestialBodyPositionsAndVelocities(float timestep) {
    for (auto& body : celestialBodies) {
        Utilities::Vector currentAcceleration = netForces[body.get()] / body->getMass();

        Utilities::Vector newPosition = body->getCurrentPosition() + body->getVelocity() * timestep + 0.5 * currentAcceleration * (timestep * timestep);

        Utilities::Vector newVelocity = body->getVelocity() + currentAcceleration * timestep;

        body->setPosition(newPosition);
        body->setVelocity(newVelocity);
    }
}

