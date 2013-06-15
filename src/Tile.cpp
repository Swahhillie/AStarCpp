#include "Tile.hpp"
#include "GameObject.hpp"
#include <assert.h>
#include "TileManager.hpp"
#include "TileGraphic.hpp"
#include <sstream>

Tile::Tile(int x, int y, TileGraphic * go) : PathNode(x, y),
 go_(go)
{
	//ctor
	assert(go_ != nullptr);
	sf::Vector2f tileSize = TileManager::getTileSize();
	go_->setPosition(tileSize.x * x, tileSize.y * y);

}

Tile::~Tile()
{
	//dtor
}
void Tile::setColor(const sf::Color & color)
{
	go_->rectangle_.setFillColor(color);
}
void Tile::setText(std::string text){go_->setText(text);}
