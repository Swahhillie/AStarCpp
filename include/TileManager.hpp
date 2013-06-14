#ifndef TILEMANAGER_HPP
#define TILEMANAGER_HPP

#include "Manager.hpp"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Tile;

class TileManager : public Manager
{
	public:
		static TileManager & instance()
		{
			static TileManager INSTANCE;
			return INSTANCE;
		}
		virtual ~TileManager();
		static sf::Vector2f getTileSize(){return sf::Vector2f(20,20);}
	protected:
	private:

		//constructors
		TileManager();
		TileManager(const TileManager& other);
		TileManager& operator=(const TileManager& other);

	private:
		//tiles
		typedef std::vector<std::unique_ptr<Tile> > Tiles;
		std::vector<Tiles> tiles_;

		int columns_;
		int rows_;

		void generateTiles();
};

#endif // TILEMANAGER_HPP
