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
	rectangle.setSize(tileSize);
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(1.0f);

	static bool initializedFont = false;
	if(!initializedFont)
	{
		bool result = debugTextFont.loadFromFile("assets/arial.ttf"); assert(result);
		initializedFont = true;

	}
	debugText.setFont(debugTextFont);
	debugText.setCharacterSize(10);
	debugText.setColor(sf::Color::Red);

}

TileGraphic::~TileGraphic()
{
	//dtor
}
void TileGraphic::draw(sf::RenderTarget & target, sf::RenderStates states)const
{
	target.draw(rectangle, states);
	target.draw(debugText, states);
}
void TileGraphic::update()
{

}
sf::Font TileGraphic::debugTextFont;
