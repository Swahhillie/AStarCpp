#include <iostream>
#include "Game.hpp"
#include "UnitTest++.h"
using namespace std;

int main(int argc, const char ** argv)
{



    int result = UnitTest::RunAllTests();
    std::cout << result << std::endl;


    Game game;

    game.executeCommandLineArguments(argc, argv);

    game.run();

    return 0;
}
