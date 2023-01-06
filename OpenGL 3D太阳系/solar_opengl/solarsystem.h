#ifndef RYAN_SOLARSYSTEM_H
#define RYAN_SOLARSYSTEM_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <vector>

#include "planet.h"

class SolarSystem
{
private:
	std::vector<Planet> planets;

public:
	SolarSystem();

	void calculatePositions(float time);
	void addPlanet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle);
	void addMoon(int planetIndex, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);
	void render();
	void renderOrbits();
	void getPlanetPosition(int index, float *vec);
	float getRadiusOfPlanet(int index);
};

#endif