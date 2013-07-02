#ifndef GAME_H
#define GAME_H

#include "Controller.hpp"
#include <SFML/Graphics.hpp>
class Scene;
class Manager;

class Game
{
public:
    Game();
    virtual ~Game();

    void build();
    void run();
    void executeCommandLineArguments(int argc, const char ** argv);

protected:
private:
    sf::RenderWindow window_;
    Controller controller_;

    std::vector<Manager*> managers_;

};

#endif // GAME_H
