#ifndef TILE_H
#define TILE_H

#include "PathNode.hpp"
#include <SFML/graphics.hpp>
class TileGraphic;
class GameObject;

class Tile : public PathNode
{
	public:
		Tile(int column, int row, TileGraphic * go);
		virtual ~Tile();

//DEBUG ONLY
		void setColor(const sf::Color & color);
		void setText(std::string text);
	protected:


	private:

		TileGraphic * go_;



};

#endif // TILE_H
