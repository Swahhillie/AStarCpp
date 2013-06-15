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


	std::stringstream sstream;
	sstream << get_x() << "," << get_y();
	go_->debugText.setString(sstream.str());
}

Tile::~Tile()
{
	//dtor
}
void Tile::setColor(const sf::Color & color)
{
	go_->rectangle.setFillColor(color);
}
