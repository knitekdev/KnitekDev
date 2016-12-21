#ifndef GAME_STATE_PLAYGAME_HPP
#define GAME_STATE_PLAYGAME_HPP

#include <SFML/Graphics.hpp>

#include "game_state.hpp"

class GameStatePlayGame : public GameState
{
private:
    sf::View gameView;
    sf::View guiView;

public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    GameStatePlayGame(Game* game);
};
#endif // GAME_STATE_PLAYGAME_HPP
