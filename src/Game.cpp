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


void Game::executeCommandLineArguments(int argc, const char ** argv)
{
	//iterate of arguments provided on the command line
	for(auto i = 1; i < argc; i++)
	{
		std::string command(argv[i]);
		//if the command contains '.lua' this is an instruction to open and execute the lua file
		if(command.find(".lua") != std::string::npos)
		{
			ScriptManager::instance().executeScriptFileAtPath(argv[i]);
		}
	}
}
