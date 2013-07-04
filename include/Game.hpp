#ifndef GAME_H
#define GAME_H

#include "Controller.hpp"
#include <SFML/Graphics.hpp>
class Scene;
class Manager;

class Game
{
public:

    static Game & instance()
    {
    	static Game INSTANCE;
    	return INSTANCE;
    }

    virtual ~Game();

    void build();
    void run();
    sf::RenderWindow & getWindow(){return window_;}
    void executeCommandLineArguments(int argc, const char ** argv);

protected:
private:
	Game();
    sf::RenderWindow window_;
    Controller controller_;

    std::vector<Manager*> managers_;

};

#endif // GAME_H
