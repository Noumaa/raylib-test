/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "Entity.h"
#include "Player.h"
#include "ResourceManager.h"
#include "World.h"

std::unique_ptr<World> world;

int main ()
{
	SearchAndSetResourceDir("resources");
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(1280, 800, "Hello Raylib");
	
	// Creating the world
	world = std::make_unique<World>(1000, 1000);

	// Creating the player
	std::unique_ptr<Entity> player(new Player(
		ResourceManager::getInstance().getTexture("angwy_wabbit_alpha.png"),
		Position(
			GetRandomValue(0, GetRenderWidth()),
			GetRandomValue(0, GetRenderHeight())
		)
	));

	// Adding the player to the world
	world->addEntity(std::move(player));

	// Add NPCs
	for (size_t i = 0; i < 10; i++)
	{
		std::unique_ptr<Entity> entity(new Entity(
			ResourceManager::getInstance().getTexture("wabbit_alpha.png"),
			Position(
				GetRandomValue(0, world->getWidth()),
				GetRandomValue(0, world->getHeight())
			)
		));

		world->addEntity(std::move(entity));
	}

	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();

		world->update(deltaTime);

		BeginDrawing();
		ClearBackground(BLACK);
	
		world->draw();
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
