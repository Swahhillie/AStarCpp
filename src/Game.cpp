#include "Game.hpp"
#include "TileManager.hpp"
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "TileManager.hpp"
#include "Time.hpp"
#include "ScriptManager.hpp"
Game::Game():
	window_(sf::VideoMode(1024, 738), "AStarCpp"),
	controller_(window_)
{
	//ctor
	managers_.push_back(&Scene::instance());
	managers_.push_back(&TileManager::instance());
	managers_.push_back(&ScriptManager::instance());
	build();
	for(auto * manager : managers_)manager->start();
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
		for(auto * manager : managers_)manager->preRender(window_);
		for(auto * manager : managers_)manager->draw(window_);
		for(auto * manager : managers_)manager->lateDraw(window_);
		for(auto * manager : managers_)manager->postRender();

	}
}


