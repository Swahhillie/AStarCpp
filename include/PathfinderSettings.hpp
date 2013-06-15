#ifndef PATHFINDERSETTINGS_H
#define PATHFINDERSETTINGS_H

class PathNode;
class Tile;
class Pathfinder;

#include <functional>
#include <vector>

class PathfinderSettings
{
	friend class Pathfinder;
public:
    PathfinderSettings();
    virtual ~PathfinderSettings();

    enum class Heuristic
    {
        Manhatten,
        Diagonal
    };
    enum class TieBreak
    {
        None,
        Simple,
        Cross
    };
    enum class ConnectedNode
    {
    	Direct,
    	All
    };
    /** \brief Change the heuristic function
     *
     * \param The new heurisic function to use.
     * \return
     *
     */

	void setHeuristic(Heuristic heuristic_);

    /** \brief Set the node finder
     *	Change the function that determines the neighbours of a node.
     * \param
     * \param
     * \return
     *
     */

	void setConnectedNodes(ConnectedNode connector);

    /** \brief Change how ties are broken
     *	None will not break ties. Simple will prefer nodes that are nearer to the destination. Cross will prefer nodes that are closer and are close to a straight line to the destination
     * \param
     * \param
     * \return
     *
     */

	void setTiebreak(TieBreak tiebreak);
private:

	Heuristic heuristic_;
    float travelCost_;
    float heuristicCost_;
    static constexpr float tieBreakAmount_ = 1.0f / 1000.0f;
    TieBreak tieBreak_;

    std::function<float(const PathNode *, const PathNode *, float cost)> heuristicFunction_;
    std::function<std::vector<Tile*>(const PathNode &)> nodeFinder_;
};
#endif // PATHFINDERSETTINGS_H
