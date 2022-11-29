#pragma once

#include "SDL.h"
#include"SDL_image.h"

#include"Tank.h"
#include"Director.h"
#include"PlayerBuilder.h"
#include"EnemyBuilder.h"
#include"AssetsStorage.h"
#include"RendererManager.h"
#include"ColisionManager.h"
#include"Map.h"
#include"TimeManager.h"
#include"InputManager.h"

/*
	Make clear functions for managers
*/

class Engine : public Component
{
	list<Component*> _componets;
	float _framerate = 0;

public:
	Engine(const char * name , int width ,int height , bool fullscreen , float framerate ) : _framerate(framerate)
	{
		RendererManager::setRenderer(name, width, height, fullscreen);
		InputManager::initInput();
		AssetsStorage::loadTiles("levels/level1scaled2.tmx");
		AssetsStorage::loadMovebles("assets/sTanks/tank.tmx");

		initComponets();
	}

	~Engine() {}

	void initComponets();

	void run();

	void draw() override
	{
		for (auto& i : _componets)
		{
			i->draw();
		}
	}

	void update() override
	{

		InputManager::update();
		for (auto& i : _componets)
		{
			i->update();
		}


	}
};