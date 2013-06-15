#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <SFML/System.hpp>
#include <list>
#include "PathfinderSettings.hpp"
class PathNode;
class Tile;
class TileManager;

class Pathfinder : sf::NonCopyable
{
    friend class PathfinderSettings;
public:
    static Pathfinder & instance()
    {
        static Pathfinder INSTANCE;
        return INSTANCE;
    }
    virtual ~Pathfinder();

    /** \brief Generate a path
     *	Generates a path through tiles in the tile manager based on PathfinderSettings.
     * \param x and y coordinates of the path start node.
     * \param x and y coordinates of the destination
     * \return A list of nodes that are connected. Starting at the origin node. If there is no path available, the list is empty.
     *
     */

    std::list<PathNode*> getPath(sf::Vector2i origin, sf::Vector2i destination);
    /** \brief Generate a path
     *	Generates a path through tiles in the tile manager based on PathfinderSettings.
     * \param The pathnode to start from
     * \param The destination node.
     * \return A list of nodes that are connected. Starting at the origin node. If there is no path available, the list is empty.
     *
     */

    std::list<PathNode*> getPath(PathNode* origin, PathNode*destination);

    /** \brief Access the settings that the pathfinder works with
     *
     * \param
     * \param
     * \return A reference to the settings
     *
     */

    PathfinderSettings & getSettings()
    {
        return settings_;
    }

protected:
private:
    Pathfinder();
    TileManager & tileManager_;

    PathfinderSettings settings_;


    static float manhattenHeuristic(const PathNode * origin, const PathNode * destination, float cost);
    static float diagonalHeuristic(const PathNode * origin, const PathNode * destination, float cost);


    std::list<PathNode*> buildPath(PathNode * destination, PathNode * start);

};

#endif // PATHFINDER_H
