#ifndef GAME_STATE_PLAYGAME_HPP
#define GAME_STATE_PLAYGAME_HPP

#include <SFML/Graphics.hpp>
#include "texture_manager.hpp"
#include "animation_handler.hpp"
#include "game_state.hpp"
#include "player.hpp"
#include "level_map.hpp"
#include "attack.hpp"
#include "monster_manager.hpp"


class GameStatePlayGame : public GameState
{
private:
    sf::View gameView;
    sf::View guiView;
    TextureManager texmgr;

public:
    Object endObiekt;
    Player player;
    LevelMap levelMap;
    Attack attackList;
    MonsterManager monsterManager;
    unsigned int levelnumber;
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
    void loadLevel();
    void loadlevelNumber();
    void checkEnd();
    GameStatePlayGame(Game* game);
};
#endif // GAME_STATE_PLAYGAME_HPP
