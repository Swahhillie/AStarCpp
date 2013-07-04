#ifndef TILEMANAGER_HPP
#define TILEMANAGER_HPP

#include "Manager.hpp"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <list>
#include "TiledWorld.hpp"

class PathNode;
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

        /** \brief Size of tiles
         *	Width and height of a single tile. used to scale and position the tiles.
         * \param
         * \param
         * \return The width and height of a tile in pixels.
         *
         */

		static sf::Vector2f getTileSize(){return tileSize_;}

        /** \brief Generates a tile map of columns * rows
         *
         * \param amount of columns to be generated
         * \param amount of rows to be generated
         * \return
         *
         */
		void generateTiles(int columns, int rows);

		typedef std::vector<Tile* > Tiles;
		const std::vector<Tiles> & getTiles()const{return tiles_;}
		std::vector<Tiles> & getTiles(){return tiles_;}

		int getColumns()const{return columns_;}
		int getRows()const{return rows_;}
		TiledWorld & getTiledWorld(){return *tiledWorld_;}
/** \brief Access a tile
 *	Lookup a tile in the tiles array. Check your input.
 * \param an sf::Vector2i or sf::Vector2u that contains the x and y coordinate of a tile.
 * \param
 * \return a pointer to the tile.
 *
 */

		template<typename T>
		Tile * getTile(const sf::Vector2<T> & coordinates)const{return tiles_[coordinates.x][coordinates.y];}

		Tile * getTile(int x_, int y)const{return tiles_[x_][y];}

		template<typename T>
		bool coordinatesAreIn(const sf::Vector2<T> & toCheck)const
		{
			return (toCheck.x >= 0 && toCheck.x < columns_ && toCheck.y >= 0 && toCheck.y < rows_);
		}

		bool coordinatesAreIn(int x_, int y)const
		{
			return (x_ >= 0 && x_ < columns_ && y >= 0 && y < rows_);
		}
        /** \brief Call a function on all Tiles
         *
         * \param A function object or lambda
         * \param
         * \return
         *
         */


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
		/** \brief Make all tiles in the map traversable
		 * This is used for some unit tests.
		 * \param
		 * \param
		 * \return
		 *
		 */

		void cleanMap(); // sets all tile to traversable

        /** \brief Make a percentage of all tiles non traversable.
         *
         * \param percentage of tiles that should be turned in to non traversable. 0 = all tiles traversable. 100 = all tiles blocked
         * \param
         * \return
         *
         */

		void generateWalls(float percentage = 0); // adds non traversable tiles to the map
	protected:
		virtual void start();
		virtual void update();
		virtual void draw(sf::RenderWindow & window);
		virtual void postRender();
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

		GameObject * tileHolder_;

		std::vector<Tile*> coloredTiles_;
		std::list<PathNode*> path_;
		static sf::Vector2f tileSize_;

		TiledWorld * tiledWorld_;

};

#endif // TILEMANAGER_HPP
