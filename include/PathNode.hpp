#ifndef PATHNODE_H
#define PATHNODE_H

class PathNode
{
	public:
		PathNode(int x, int y);
		virtual ~PathNode();

		int get_x(){return x_;}
		int get_y(){return y_;}
	protected:
	private:

		int x_;
		int y_;
};

#endif // PATHNODE_H
