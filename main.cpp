#include "game.hpp"
#include "game_state_startmenu.hpp"
#include <locale>
#include <iostream>

int main()
{
    std::setlocale( LC_ALL, "polish" );
    Game game;
    game.pushState(new GameStateStartMenu(&game));
    game.gameLoop();

    return 0;
}
