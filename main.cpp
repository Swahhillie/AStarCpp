#include <iostream>
#include "Game.hpp"
#include "UnitTest++.h"
using namespace std;

int main()
{






    int result = UnitTest::RunAllTests();
    std::cout << result << std::endl;


    Game game;
    game.run();

    return 0;
}
