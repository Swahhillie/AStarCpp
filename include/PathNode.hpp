#ifndef PATHNODE_H
#define PATHNODE_H

#include <vector>
#include <SFML/Graphics.hpp>
class PathNode
{
	public:
		PathNode(int x, int y);
		virtual ~PathNode();

		int get_x(){return coordinates_.x;}
		int get_y(){return coordinates_.y;}
		sf::Vector2i getCoordinates()const{return coordinates_;}

		std::vector<sf::Vector2i> getDirectNeighbours();
		std::vector<sf::Vector2i> getAllNeighbours();
	protected:
	private:

		sf::Vector2i coordinates_;

		int & x_;
		int & y_;
};

#endif // PATHNODE_H
