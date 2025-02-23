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

Camera2D camera;

int main ()
{
	SearchAndSetResourceDir("resources");
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(1280, 800, "Hello Raylib");
	
	// Creating the camera
	camera = { 0 };
	camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	
	// Creating the world
	world = std::make_unique<World>(1000, 1000);
	
	// Creating the player
	Player* player = new Player(
		ResourceManager::getInstance().getTexture("angwy_wabbit_alpha.png"),
		{
			world->getWidth() / 2,
			world->getHeight() / 2
		}
	);

	// Passing a camera pointer to the player
	player->setCamera(&camera);

	// Adding the player to the world
	world->addEntity(std::unique_ptr<Player>(player));

	// Add NPCs
	for (size_t i = 0; i < 10; i++)
	{
		std::unique_ptr<Entity> entity(new Entity(
			ResourceManager::getInstance().getTexture("wabbit_alpha.png"),
			{
				GetRandomValue(0, world->getWidth()),
				GetRandomValue(0, world->getHeight())
			}
		));

		world->addEntity(std::move(entity));
	}

	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();

		world->update(deltaTime);
	
		BeginDrawing();

		ClearBackground(BLACK);
	
		world->draw(camera);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
