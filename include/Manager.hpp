#ifndef MANAGER_H
#define MANAGER_H

#include <SFML/System.hpp>

class Manager : public sf::NonCopyable
{
	public:

		virtual ~Manager();

	protected:
		Manager();
	private:

		Manager(const Manager& other);
		Manager& operator=(const Manager& other);
};

#endif // MANAGER_H
