#ifndef TILEMANAGER_HPP
#define TILEMANAGER_HPP

#include "Manager.hpp"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Tile;
class GameObject;
class TileManager : public Manager
{
	public:
		static TileManager & instance()
		{
			static TileManager INSTANCE;
			return INSTANCE;
		}
		virtual ~TileManager();
		static sf::Vector2f getTileSize(){return sf::Vector2f(30,30);}
		typedef std::vector<std::unique_ptr<Tile> > Tiles;
		const std::vector<Tiles> & getTiles()const{return tiles_;}
		std::vector<Tiles> & getTiles(){return tiles_;}

		int getColumns(){return columns_;}
		int getRows(){return rows_;}

		template<typename T>
		Tile & getTile(const sf::Vector2<T> & coordinates)const{return *tiles_[coordinates.x][coordinates.y];}

		template<typename T>
		bool coordinatesAreIn(const sf::Vector2<T> & toCheck)const
		{
			return (toCheck.x >= 0 && toCheck.x < columns_ && toCheck.y >= 0 && toCheck.y < rows_);
		}

		bool coordinatesAreIn(int x, int y)const
		{
			return (x >= 0 && x < columns_ && y >= 0 && y < rows_);
		}

		template<typename Func>
		void forEachTile(Func func)
		{
			for(auto i = 0u; i < tiles_.size(); i++){
				auto & col = tiles_[i];
				for(auto j = 0u; j < col.size(); j++)
				{
					func(*col[j]);
				}
			}
		}

	protected:
		virtual void update();
		virtual void onPostRender();
	private:

		//constructors
		TileManager();
		TileManager(const TileManager& other);
		TileManager& operator=(const TileManager& other);

	private:
		//tiles
		std::vector<Tiles> tiles_;

		int columns_;
		int rows_;

		void generateTiles();

		GameObject * tileHolder_;

		std::vector<sf::Vector2i> coloredTileCoordinates_;

};

#endif // TILEMANAGER_HPP
