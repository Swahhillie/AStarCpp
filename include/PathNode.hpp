#ifndef PATHNODE_H
#define PATHNODE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
class Tile;

class PathNode : sf::NonCopyable
{
	public:
		PathNode(int x, int y);
		virtual ~PathNode();

		int get_x()const{return coordinates_.x;}
		int get_y()const{return coordinates_.y;}
		sf::Vector2i getCoordinates()const{return coordinates_;}

		std::vector<Tile*> getDirectNeighbours()const;
		std::vector<Tile*> getAllNeighbours()const;

		float g_;
		float h_;
		float f_;
		PathNode * parentNode_;

		virtual bool traversable()const{return true;}
	protected:
	private:

		sf::Vector2i coordinates_;

		int & x_;
		int & y_;
};

#endif // PATHNODE_H
