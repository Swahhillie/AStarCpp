#ifndef PATHNODE_H
#define PATHNODE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
class Tile;

class PathNode : sf::NonCopyable
{
	public:
		PathNode(int x_, int y);
		virtual ~PathNode();

		const sf::Vector2i & getCoordinates()const{return coordinates_;}

		std::vector<Tile*> getDirectNeighbours()const;
		std::vector<Tile*> getAllNeighbours()const;

		float g_;
		float h_;
		float f_;
		PathNode * parentNode_;



		virtual bool traversable()const{return true;}
		virtual float getTravelCost()const{return 0.0f;};
	protected:
	private:

		const sf::Vector2i coordinates_;
	public:
		const int x_;
		const int y_;

};

#endif // PATHNODE_H
