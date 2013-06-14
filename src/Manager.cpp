#include "Manager.hpp"

Manager::Manager()
{
	//ctor
}

Manager::~Manager()
{
	//dtor
}

Manager::Manager(const Manager& other)
{
	//copy ctor
}

Manager& Manager::operator=(const Manager& rhs)
{
	if (this == &rhs) return *this; // handle self assignment
	//assignment operator
	return *this;
}
