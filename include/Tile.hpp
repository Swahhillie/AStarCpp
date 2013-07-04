#ifndef TILE_H
#define TILE_H

#include "PathNode.hpp"
#include <SFML/graphics.hpp>
class TileGraphic;
class GameObject;

class Tile : public PathNode
{
	public:
		Tile(int column, int row);
		virtual ~Tile();

//DEBUG ONLY
		void recolor();
		void loadFromTiledFile();
		void setColor(const sf::Color & color);
		void setText(std::string text);
		void setTraversable(bool value);

		virtual bool traversable()
		{
			return isTraversable_;
		}

		std::string getTilePropertiesString()const;
	protected:


	private:


		bool isTraversable_;
		unsigned int tiledNodeId_;

		static const sf::Color defaultColor;
		static const sf::Color nonTraversableColor;

		sf::Text txt_;



};

#endif // TILE_H
