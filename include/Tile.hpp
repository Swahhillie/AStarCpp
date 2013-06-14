#ifndef TILE_H
#define TILE_H

#include "PathNode.hpp"
class GameObject;

class Tile : public PathNode
{
	public:
		Tile(int column, int row, GameObject * go);
		virtual ~Tile();

	protected:
	private:

		GameObject * go_;

};

#endif // TILE_H
