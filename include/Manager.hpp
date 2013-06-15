#ifndef MANAGER_H
#define MANAGER_H

#include <SFML/System.hpp>
class Game;
class Manager : public sf::NonCopyable
{
	friend class Game;
	public:

		virtual ~Manager();

	protected:
		Manager();
		virtual void preUpdate(){}
		virtual void update(){}
		virtual void lateUpdate(){}
		virtual void onPreRender(){}
		virtual void onPostRender(){}


	private:

		Manager(const Manager& other);
		Manager& operator=(const Manager& other);
};

#endif // MANAGER_H
