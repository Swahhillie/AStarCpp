#ifndef MANAGER_H
#define MANAGER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
class Game;

class Manager : public sf::NonCopyable
{
	friend class Game;
	public:

		virtual ~Manager();

	protected:
		Manager();
		virtual void start(){}

		virtual void preUpdate(){}
		virtual void update(){}
		virtual void lateUpdate(){}
		virtual void preRender(sf::RenderWindow & window){}
		virtual void draw(sf::RenderWindow & window){}
		virtual void lateDraw(sf::RenderWindow & window){}
		virtual void postRender(){}


	private:

		Manager(const Manager& other);
		Manager& operator=(const Manager& other);
};

#endif // MANAGER_H
