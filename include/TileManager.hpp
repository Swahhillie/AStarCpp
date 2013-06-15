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

        /** \brief Size of tiles
         *	Width and height of a single tile. used to scale and position the tiles.
         * \param
         * \param
         * \return
         *
         */

		static sf::Vector2f getTileSize()const{return sf::Vector2f(30,30);}

        /** \brief
         *
         * \param
         * \param
         * \return
         *
         */

		typedef std::vector<Tile* > Tiles;
		const std::vector<Tiles> & getTiles()const{return tiles_;}
		std::vector<Tiles> & getTiles(){return tiles_;}

		int getColumns()const{return columns_;}
		int getRows()const{return rows_;}
/** \brief Access a tile
 *	Lookup a tile in the tiles array. Check your input.
 * \param an sf::Vector2i or sf::Vector2u that contains the x and y coordinate of a tile.
 * \param
 * \return a pointer to the tile.
 *
 */

		template<typename T>
		Tile * getTile(const sf::Vector2<T> & coordinates)const{return tiles_[coordinates.x][coordinates.y];}

		Tile * getTile(int x, int y)const{return tiles_[x][y];}

		template<typename T>
		bool coordinatesAreIn(const sf::Vector2<T> & toCheck)const
		{
			return (toCheck.x >= 0 && toCheck.x < columns_ && toCheck.y >= 0 && toCheck.y < rows_);
		}

		bool coordinatesAreIn(int x, int y)const
		{
			return (x >= 0 && x < columns_ && y >= 0 && y < rows_);
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

		std::vector<Tile*> coloredTiles_;

};

#endif // TILEMANAGER_HPP
