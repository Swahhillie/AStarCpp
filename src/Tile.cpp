#include "Tile.hpp"
#include "GameObject.hpp"
#include <assert.h>
#include "TileManager.hpp"

Tile::Tile(int x, int y, GameObject * go) : PathNode(x, y),
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
