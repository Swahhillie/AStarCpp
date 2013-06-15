#include "Game.hpp"
#include "TileManager.hpp"
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "TileManager.hpp"
#include "Time.hpp"

Game::Game():
	window_(sf::VideoMode(1024, 738), "AStarCpp"),
	controller_(window_),
	scene_(Scene::instance())
{
	//ctor
	scene_.setWindow(&window_);
	managers_.push_back(&Scene::instance());
	managers_.push_back(&TileManager::instance());
	build();
}

Game::~Game()
{
	//dtor
}

void Game::build()
{
	TileManager::instance();
}

void Game::run()
{
	while(controller_.running())
	{
		Time::update();
		controller_.update();
		for(auto * manager : managers_)manager->preUpdate();
		for(auto * manager : managers_)manager->update();
		for(auto * manager : managers_)manager->lateUpdate();
		for(auto * manager : managers_)manager->onPreRender();
		scene_.draw();
		for(auto * manager : managers_)manager->onPostRender();

	}
}


