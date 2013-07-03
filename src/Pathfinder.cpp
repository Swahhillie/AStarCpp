#include "Pathfinder.hpp"
#include <list>
#include "TileManager.hpp"
#include "Tile.hpp"
#include "UnitTest++.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <assert.h>


Pathfinder::Pathfinder():
    tileManager_(TileManager::instance())

{
    //ctor
}

Pathfinder::~Pathfinder()
{
    //dtor
}


std::list<PathNode*> Pathfinder::getPath(sf::Vector2i origin, sf::Vector2i destination)
{
    assert(TileManager::instance().coordinatesAreIn(origin));
    assert(TileManager::instance().coordinatesAreIn(destination));
    PathNode * firstNode = tileManager_.getTile(origin);
    PathNode * destinationNode = tileManager_.getTile(destination);

    return getPath(firstNode, destinationNode);
}
std::list<PathNode*> Pathfinder::getPath(PathNode * firstNode, PathNode * destinationNode)
{
    assert(firstNode != nullptr);
    assert(destinationNode != nullptr);

    std::list<PathNode*> openNodes;
    std::list<PathNode*> closedNodes;

    PathNode * currentNode = firstNode;



    float g = 0;
    float h = 0;
    float f = 0;

    currentNode->g_ = 0;
    currentNode->h_ = settings_.heuristicFunction_(currentNode, destinationNode, settings_.heuristicCost_);
    currentNode->f_ = currentNode->g_ + currentNode->h_;

    std::list<PathNode*> path;

	//both these options will lead to a full search of the grid. early out
    if(!destinationNode->traversable() ||  !firstNode->traversable())
    {

        return path;
    }

    while(currentNode != destinationNode)
    {
        //auto connectedNodes = currentNode->getDirectNeighbours();
        auto connectedNodes = settings_.nodeFinder_(*currentNode);
        //iterate over all neighbours of the current node
        for( auto * testNode : connectedNodes)
        {

            if(!testNode->traversable() || !currentNode->traversable())continue;
            if(testNode == currentNode) continue;


            g = currentNode->g_ + settings_.heuristicFunction_(currentNode, testNode, settings_.travelCost_); // the cost to make a step
            g += testNode->getTravelCost();
            h = settings_.heuristicFunction_(testNode, destinationNode, settings_.heuristicCost_);

            //straight up tiebreak
            if(settings_.tieBreak_ == PathfinderSettings::TieBreak::Simple) h *= 1.0f + settings_.tieBreakAmount_;
            else if(settings_.tieBreak_ == PathfinderSettings::TieBreak::Cross)
            {
                //cross product tiebreak
                auto dx1 = currentNode->x_ - destinationNode->x_;
                auto dy1 = currentNode->y_ - destinationNode->y_;

                auto dx2 = firstNode->x_ - destinationNode->x_;
                auto dy2 = firstNode->y_ - destinationNode->y_;
                auto cross = abs(dx1 * dy2 - dx2 * dy1);
                h += cross * settings_.tieBreakAmount_;
            }

            f = g + h;

            if(std::find(openNodes.begin(), openNodes.end(), testNode) != openNodes.end() || std::find(closedNodes.begin(), closedNodes.end(), testNode) != closedNodes.end())
            {
                if(testNode->f_ > f)
                {
                    testNode->g_ = g;
                    testNode->h_ = h;
                    testNode->f_ = f;
                    testNode->parentNode_ = currentNode;
                }
            }
            else
            {
                testNode->g_ = g;
                testNode->h_ = h;
                testNode->f_ = f;
                testNode->parentNode_ = currentNode;
                openNodes.push_front(testNode);
            }

        }
        closedNodes.push_front(currentNode);

        //there are no more open nodes.
        if(openNodes.size() == 0)
        {
            return path; // no path
        }

        //sort on f

        openNodes.sort([](const PathNode * a, const PathNode * b)
        {
            return a->f_ < b->f_;
        });

        currentNode = openNodes.front();
        openNodes.pop_front();
    }

    return buildPath(destinationNode, firstNode);
}
std::list<PathNode*> Pathfinder::buildPath(PathNode * destination, PathNode * start)
{
    std::list<PathNode*> path;
    auto * current = destination;
    path.push_front(destination);
    while(current != start)
    {
        current = current->parentNode_;
        path.push_front(current);
    }

    return path;
}
float Pathfinder::manhattenHeuristic(const PathNode * start, const PathNode * destination, float cost)
{
    auto dx = abs(start->x_ - destination->x_);
    auto dy = abs(start->y_ - destination->y_);
    return (dx + dy) * cost;
}

float Pathfinder::diagonalHeuristic(const PathNode * start, const PathNode * destination, float cost)
{
    float cost2 = sqrtf(2.0f) *cost;
    auto dx = abs(start->x_ - destination->x_);
    auto dy = abs(start->y_ - destination->y_);
    return cost * (dx + dy) + (cost2 - 2 * cost) * std::min(dx, dy);

}

TEST(oneStepPath)
{
    auto path = Pathfinder::instance().getPath(sf::Vector2i(0,0), sf::Vector2i(1,0));
    CHECK_EQUAL(2u, path.size());
}

TEST(tenStepsRightPath)
{
    auto path = Pathfinder::instance().getPath(sf::Vector2i(0,0), sf::Vector2i(10,0));
    CHECK_EQUAL(11u, path.size());
}

TEST(tenStepsDown)
{
    auto path = Pathfinder::instance().getPath(sf::Vector2i(0,0), sf::Vector2i(0,10));
    CHECK_EQUAL(11u, path.size());
}

TEST(pathIsStraight)
{
    auto path = Pathfinder::instance().getPath(sf::Vector2i(0,0), sf::Vector2i(10,0));

    TileManager & tileManager = TileManager::instance();
    std::vector<PathNode*> hardPath(11u);

    for(auto i = 0; i < 11; i++)
    {
        hardPath[i] = tileManager.getTile(i, 0);
    }

    int i = 0;
    for(auto * pn : path)
    {

        CHECK_EQUAL(hardPath[i], pn);
        i++;
    }

}
TEST(oneRightOneDownDirect)
{

    Pathfinder & pathfinder = Pathfinder::instance();
    //store old settings
    PathfinderSettings oldSettings(pathfinder.getSettings());
    //change settings
    pathfinder.getSettings().setConnectedNodes(PathfinderSettings::ConnectedNode::Direct);
    auto path = pathfinder.getPath(sf::Vector2i(0, 0), sf::Vector2i(1,1));

    CHECK_EQUAL(3u, path.size());

    //restore old settings
    pathfinder.getSettings() = oldSettings;
}

TEST(ghfValues)
{
    Pathfinder & pathfinder = Pathfinder::instance();
//store old settings
    PathfinderSettings oldSettings(pathfinder.getSettings());
    //change settings
    pathfinder.getSettings().setConnectedNodes(PathfinderSettings::ConnectedNode::Direct);
    TileManager& tileManager = TileManager::instance();
    auto path = pathfinder.getPath(tileManager.getTile(0,0), tileManager.getTile(5,5));
    for(auto * pn : path)
    {
        CHECK_CLOSE(pn->g_ + pn->h_, pn->f_, 0.001f);
    }
    CHECK_EQUAL(11u, path.size());
    pathfinder.getSettings() = oldSettings;
}
