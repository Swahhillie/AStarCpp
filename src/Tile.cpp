#include "Tile.hpp"
#include "GameObject.hpp"
#include <assert.h>
#include "TileManager.hpp"
#include "TileGraphic.hpp"
#include <sstream>
#include "Random.hpp"

Tile::Tile(int x, int y) : PathNode(x, y),
 isTraversable_(true)
{
	//ctor
	//sf::Vector2f tileSize = TileManager::getTileSize();



}

Tile::~Tile()
{
	//dtor
}
void Tile::setColor(const sf::Color & color)
{
	//go_->rectangle_.setFillColor(color);
}
void Tile::setText(std::string text)
{
    //go_->setText(text);
}
void Tile::setTraversable(bool value)
{
	if(value)
	{
		//don't change the color if the node is traversable
	}
	else
	{
		//go_->rectangle_.setFillColor(sf::Color::Black);
	}
	isTraversable_ = value;
}
void Tile::recolor()
{
	if(isTraversable_)
	{
		setColor(defaultColor);
	}
	else
	{
		setColor(nonTraversableColor);
	}
}
const sf::Color Tile::defaultColor = sf::Color::White;
const sf::Color Tile::nonTraversableColor = sf::Color::Black;
