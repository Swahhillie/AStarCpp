#include "PathfinderSettings.hpp"

#include "Tile.hpp"
#include "Pathfinder.hpp"
#include <assert.h>

PathfinderSettings::PathfinderSettings():
    heuristic_(Heuristic::Manhatten),
    travelCost_(1.0f),
    heuristicCost_(1.0f),
    tieBreak_(TieBreak::Cross),
    heuristicFunction_(&Pathfinder::manhattenHeuristic),
    nodeFinder_(&PathNode::getAllNeighbours)
{
}

PathfinderSettings::~PathfinderSettings()
{
    //dtor
}
void PathfinderSettings::setConnectedNodes(ConnectedNode c)
{
	switch(c)
	{
	case ConnectedNode::All:
		nodeFinder_ = &PathNode::getAllNeighbours;
		break;
	case ConnectedNode::Direct:
		nodeFinder_ = &PathNode::getDirectNeighbours;
		break;
	}
}
void PathfinderSettings::setHeuristic(Heuristic h)
{
	switch(h)
	{
	case Heuristic::Manhatten:
		heuristicFunction_ = &Pathfinder::manhattenHeuristic;
		break;
	case Heuristic::Diagonal:
		heuristicFunction_ = &Pathfinder::diagonalHeuristic;
		break;
	}
}
void PathfinderSettings::setTiebreak(TieBreak t)
{
	tieBreak_ = t;
}
