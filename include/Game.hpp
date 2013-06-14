#ifndef GAME_H
#define GAME_H

#include "DavidH/Controller.hpp"
#include <SFML/Graphics.hpp>
class Scene;

class Game
{
	public:
		Game();
		virtual ~Game();

		void build();
		void run();

	protected:
	private:
		sf::RenderWindow window_;
		Controller controller_;
		Scene & scene_;


};

#endif // GAME_H
