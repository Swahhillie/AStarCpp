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
void Tile::setTexCoords()const
{
	TiledFile & tiledFile = TileManager::instance().getTiledWorld().getTiledFile();
	auto tileInd = x_ * tiledFile.width + y_;
	const TiledFile::TileSet & tileset = tiledFile.tilesets[0];
	auto imagesX = (tileset.imagewidth - tileset.margin) / (tileset.tilewidth + tileset.margin);
	auto imagesY = (tileset.imageheight - tileset.margin) / (tileset.tileheight + tileset.margin);

	auto imageInd = tiledFile.layers[0].data[tileInd] -1;

	sf::VertexArray & quads = TileManager::instance().getTiledWorld().getQuads();
	auto vertexIndex = tileInd * 4;

	auto c = (imageInd  % imagesX);
	auto marginX = c * tileset.margin + tileset.margin;

	auto r = (imageInd  / imagesX);
	auto marginY = r * tileset.margin + tileset.margin;

	c *= tileset.tilewidth;
	r *= tileset.tileheight;
	c += marginX;
	r += marginY;

	quads[vertexIndex + 0].texCoords = sf::Vector2f(c , r); //tl
	quads[vertexIndex + 1].texCoords = sf::Vector2f(c + tiledFile.tilewidth, r); // tr
	quads[vertexIndex + 2].texCoords = sf::Vector2f(c + tiledFile.tilewidth, r + tiledFile.tileheight); //br
	quads[vertexIndex + 3].texCoords = sf::Vector2f(c, r + tiledFile.tileheight); //bl

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
