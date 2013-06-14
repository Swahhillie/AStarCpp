#include "Game.hpp"
#include "TileManager.hpp"
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Time.hpp"

Game::Game():
	window_(sf::VideoMode(1024, 738), "AStarCpp"),
	controller_(window_),
	scene_(Scene::instance())
{
	//ctor
	scene_.window_ = &window_;
	build();
}

Game::~Game()
{
	//dtor
}

void Game::build()
{
	TileManager & tileManager = TileManager::instance();
}

void Game::run()
{
	while(controller_.running())
	{
		Time::update();
		controller_.update();
		scene_.update();
		scene_.draw();

	}
}
