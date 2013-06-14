#include "TileGraphic.hpp"
#include <iostream>
#include "Time.hpp"
#include "TileManager.hpp"
TileGraphic::TileGraphic(std::string name)
: GameObject(name)
{
	//ctor

	sf::Vector2f tileSize = TileManager::getTileSize();
	rectangle.setSize(tileSize);
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(1.0f);
}

TileGraphic::~TileGraphic()
{
	//dtor
}
void TileGraphic::draw(sf::RenderTarget & target, sf::RenderStates states)const
{
	target.draw(rectangle, states);
}
void TileGraphic::update()
{

}
