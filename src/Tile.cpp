#include "Tile.hpp"
#include "GameObject.hpp"
#include <assert.h>
#include "TileManager.hpp"
#include "TileGraphic.hpp"
#include <sstream>
#include "Random.hpp"


Tile::Tile(int x, int y) : PathNode(x, y),
    isTraversable_(true),
    tiledNodeId_(0u)
{
    //ctor
    //sf::Vector2f tileSize = TileManager::getTileSize();



}

Tile::~Tile()
{
    //dtor
}
void Tile::loadFromTiledFile()
{
    //set vertex coordinates

    TiledFile & tiledFile = TileManager::instance().getTiledWorld().getTiledFile();
    auto tileInd = getIndex();
    const TiledFile::TileSet & tileset = tiledFile.tilesets[0];

    //calculate how many tiles go in the x and y direction
    auto imagesX = (tileset.imagewidth - tileset.margin) / (tileset.tilewidth + tileset.margin);
//    auto imagesY = (tileset.imageheight - tileset.margin) / (tileset.tileheight + tileset.margin);

    //get the image that belongs to this position in the tile array
    tiledNodeId_ = tiledFile.layers[0].data[tileInd];

	auto imageInd =  tiledNodeId_ -1;

    sf::VertexArray & quads = TileManager::instance().getTiledWorld().getQuads();

    // there are 4 vertices per quad and 1 quad per tile.
    auto vertexIndex = tileInd * 4;

    //calculate how many steps the picture is in the x direction
    auto c = (imageInd  % imagesX);
    auto marginX = c * tileset.margin + tileset.margin;

    //calculate how many steps the picture is in the y direction
    auto r = (imageInd  / imagesX);
    auto marginY = r * tileset.margin + tileset.margin;

    //multiply by the width of a tile and add the margin between the tiles
    c *= tileset.tilewidth;
    r *= tileset.tileheight;
    c += marginX;
    r += marginY;

    //set the texCoords
    quads[vertexIndex + 0].texCoords = sf::Vector2f(c , r); //tl
    quads[vertexIndex + 1].texCoords = sf::Vector2f(c + tiledFile.tilewidth, r); // tr
    quads[vertexIndex + 2].texCoords = sf::Vector2f(c + tiledFile.tilewidth, r + tiledFile.tileheight); //br
    quads[vertexIndex + 3].texCoords = sf::Vector2f(c, r + tiledFile.tileheight); //bl

    if(tiledNodeId_ != 30u) setTraversable(false);

}
std::string Tile::getTilePropertiesString()const{
	//tile properties
	std::stringstream stream;
	TiledFile::TileSet tileset = TileManager::instance().getTiledWorld().getTiledFile().tilesets[0];

    stream << "col, row = " << x_ << "," << y_ << "\n";
    stream << "index = " << getIndex() << "\n";
    stream << "node = " << tiledNodeId_ << "{";

    auto it = tileset.tileproperties.find(tiledNodeId_);
    if(it != tileset.tileproperties.end())
    {
		stream << "\n";
		for(auto jt : it->second)
		{
			stream << "\t" << jt.first << " = " << jt.second << "\n";
		}

    }
    stream << "}" << "\n";
    return stream.str();

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
