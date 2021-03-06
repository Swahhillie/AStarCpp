#include "PathNode.hpp"
#include "Scene.hpp"
#include "TileManager.hpp"
#include <assert.h>
#include "UnitTest++.h"
#include "Tile.hpp"

PathNode::PathNode(int px, int py):
    g_(0),
    h_(0),
    f_(0),
    parentNode_(nullptr),
    coordinates_(sf::Vector2i(px, py)),
    x_(px),
    y_(py)
{
    //ctor
    //std::cout << "x " << coordinates_.x << ", y " << coordinates_.y << std::endl;
}

PathNode::~PathNode()
{
    //dtor
}
std::vector<Tile *> PathNode::getDirectNeighbours()const
{
    //direct connections
    std::vector<Tile *> neighbours;
    TileManager & tileManager = TileManager::instance();
    auto & tiles = tileManager.getTiles();

    if(x_ > 0)
    {
        neighbours.push_back(tiles[x_-1][y_]);
    }
    if(x_ + 1 < tileManager.getColumns())
    {
        neighbours.push_back(tiles[x_+1][y_]);
    }
    if(y_ > 0)
    {
        neighbours.push_back(tiles[x_][y_-1]);
    }
    if(y_ + 1 < tileManager.getRows())
    {
        neighbours.push_back(tiles[x_][y_+1]);
    }
    return neighbours;
}
std::vector<Tile*> PathNode::getAllNeighbours()const
{
    std::vector<Tile*> neighbours;
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
    for(int x = x_ -1; x < x_ + 2; x++)
        for(int y = y_ -1; y < y_ + 2; y++)
        {
            if(tileManager.coordinatesAreIn(x, y))
            {
                neighbours.push_back(tileManager.getTile(x,y));
            }
        }
    return neighbours;
}
unsigned int PathNode::getIndex()const
{
	return y_ * TileManager::instance().getColumns() + x_;
};

