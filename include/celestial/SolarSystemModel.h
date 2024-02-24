
#ifndef SOLARSYSTEMMODEL_H
#define SOLARSYSTEMMODEL_H

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <optional>
#include <unordered_map>
#include <utility>
#include <future>
#include <atomic>
#include <iostream>
#include <utils/Vector.h>
#include <celestial/CelestialBody.h>
#include <utils/PairDefinitions.h>
#include <utils/MathUtils.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace SolarSystem {

	class SolarSystemModel {

	public:

		SolarSystemModel() = default;

		inline void addCelestialBody(std::unique_ptr<CelestialBody> celestialBody) {
			this->celestialBodies.push_back(std::move(celestialBody));
		}

		const std::vector<std::unique_ptr<CelestialBody>>& getCelestialBodies() const {
			return this->celestialBodies;
		}

		std::pair<int, Utilities::Vector> getForceBetweenBodies(const CelestialBody* body1, const CelestialBody* body2) const;

		void removeCelestialBody(const std::string& name);

		int determineNewScore(const Utilities::Vector& force, float timestep);

		int adjustScoreBasedOnTimestep(int currentScore, float timestep, float fps);
		
		void processForceCalculationForPair(const std::pair<const CelestialBody*, const CelestialBody*>& pair, int& score,Utilities::Vector& force, float timestep, float fps);
	
		void calculateForceVectorsBasedOnTimestep(float timestep, float fps);

		void calculateForceVectorsBasedOnTimestepParrallelized(float timestep, float fps);

		void calculateTotalForces();

		void updateCelestialBodyPositionsAndVelocities(float timestep);

		// Method to initialize the rendering context
		void initializeRendering(Utilities::GeometryManager& geomManager);

		// Method to render the scene
		void render();

		inline void setShaderProgram(GLuint shaderProgram) {
			this->shaderProgram = shaderProgram;
		}

	private:

		std::vector<std::unique_ptr<CelestialBody>> celestialBodies;		
		std::unordered_map<std::pair<const CelestialBody*, const CelestialBody*>, std::pair<int, Utilities::Vector>, Utilities::PairHash, Utilities::PairEqual> forceCalculationMap;
		std::unordered_map<const CelestialBody*, Utilities::Vector> netForces;
		GLuint shaderProgram;

	};
}

#endif