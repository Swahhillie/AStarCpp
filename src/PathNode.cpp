#include "PathNode.hpp"
#include "Scene.hpp"
#include "TileManager.hpp"
#include <assert.h>
#include "UnitTest++.h"
#include "Tile.hpp"

PathNode::PathNode(int x, int y):
    coordinates_(sf::Vector2u(x, y)),
    x_(coordinates_.x),
    y_(coordinates_.y)
{
    //ctor
}

PathNode::~PathNode()
{
    //dtor
}
std::vector<sf::Vector2i> PathNode::getDirectNeighbours()
{
    //direct connections
    std::vector<sf::Vector2i> neighbours;
    TileManager & tileManager = TileManager::instance();

    if(x_ > 0)
    {
        neighbours.push_back(sf::Vector2i(x_-1,y_));
    }
    if(x_ + 1 < tileManager.getColumns())
    {
        neighbours.push_back(sf::Vector2i(x_+1,y_));
    }
    if(y_ > 0)
    {
        neighbours.push_back(sf::Vector2i(x_,y_-1));
    }
    if(y_ + 1 < tileManager.getRows())
    {
        neighbours.push_back(sf::Vector2i(x_,y_+1));
    }
    return neighbours;
}
std::vector<sf::Vector2i> PathNode::getAllNeighbours()
{
	std::vector<sf::Vector2i> neighbours;
	TileManager& tileManager = TileManager::instance();
	/*
	for(auto i = 0; i < 9; i++)
	{
		int dx = (i % 3) - 1; // -1, 0, 1, -1, 0, 1, -1, 0, 1
		int dy = ((i / 3) % 3) -1; // -1, -1, -1, 0, 0, 0, 1, 1, 1,
		sf::Vector2i toCheck = getCoordinates() + sf::Vector2i(dx, dy);
		if(tileManager.coordinatesAreIn(toCheck))
		{
			neighbours.push_back(toCheck);
		}
	}
	*/
	for(auto x = x_ -1; x < x_ + 2; x++)
	for(auto y = y_ -1; y < y_ + 2; y++){
		if(tileManager.coordinatesAreIn(x, y))
		{
			neighbours.push_back(sf::Vector2i(x, y));
		}
	}
	return neighbours;
}
