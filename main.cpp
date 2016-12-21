#include "game.hpp"
#include "game_state_startmenu.hpp"

int main()
{
    Game game;
    game.pushState(new GameStateStartMenu(&game));
    game.gameLoop();

    return 0;
}
