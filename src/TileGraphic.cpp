#include "TileGraphic.hpp"
#include <iostream>
#include "Time.hpp"
#include "TileManager.hpp"
#include <assert.h>

TileGraphic::TileGraphic(std::string name)
: GameObject(name)
{
	//ctor

	sf::Vector2f tileSize = TileManager::getTileSize();
	rectangle_.setSize(tileSize);
	rectangle_.setOutlineColor(sf::Color::Red);
	rectangle_.setOutlineThickness(1.0f);

	static bool initializedFont = false;
	if(!initializedFont)
	{
		bool result = debugTextFont_.loadFromFile("assets/arial.ttf"); assert(result);
		initializedFont = true;

	}
	debugText_.setFont(debugTextFont_);
	debugText_.setCharacterSize(9);
	debugText_.setColor(sf::Color::Red);

}

TileGraphic::~TileGraphic()
{
	//dtor
}
void TileGraphic::draw(sf::RenderTarget & target, sf::RenderStates states)const
{
	target.draw(rectangle_, states);
	target.draw(debugText_, states);
}
void TileGraphic::update()
{

}
sf::Font TileGraphic::debugTextFont_;
