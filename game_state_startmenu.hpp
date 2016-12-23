#ifndef GAME_STATE_STARTMENU_HPP
#define GAME_STATE_STARTMENU_HPP

#include <SFML/Graphics.hpp>

#include "game_state.hpp"
#include "menu_gui.hpp"

class GameStateStartMenu : public GameState
{
private:
    sf::View view;
    void loadgame();
public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
    GameStateStartMenu(Game* game);
    GuiMenu guiMenu;
};

#endif //GAME_STATE_STARTMENU_HPP
