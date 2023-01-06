#pragma warning(disable : 4996)

#include "solarsystem.h"

SolarSystem::SolarSystem()
{
}

// 计算天体位置
void SolarSystem::calculatePositions(float time)
{
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].calculatePosition(time);
	}
}

// 添加天体
void SolarSystem::addPlanet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	planets.push_back(Planet(distanceFromSun, orbitTime, rotationTime, radius, textureHandle));
}

// 添加卫星
void SolarSystem::addMoon(int planetIndex, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	planets[planetIndex].addMoon(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle);
}

// 渲染天体
void SolarSystem::render()
{
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].render();
	}
}

// 渲染运行轨道
void SolarSystem::renderOrbits()
{
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].renderOrbit();
	}
}

// 获取天体位置
void SolarSystem::getPlanetPosition(int index, float *vec)
{
	planets[index].getPosition(vec);
}

// 获取天体半径
float SolarSystem::getRadiusOfPlanet(int index)
{
	return planets[index].getRadius();
}