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
#include "game_gui.hpp"
#include "Testing_Tool.hpp"
#include "SoundManager.hpp"
#include <iostream>


class GameStatePlayGame : public GameState
{
private:
    const float defaultWidth = 1280.0f;
    const float defaultHeight = 720.0f;
    sf::View gameView;
    sf::View guiView;
    TextureManager texmgr;
    SoundManager soundMgr;
    bool playerIsMoving;
    bool updateWhenMove;
public:
    float gameSpeed;
    Object endObiekt;
    Player player;
    LevelMap levelMap;
    Attack attackList;
    HitList hitList;
    MonsterManager monsterManager;
    GameGui gameGui;
    unsigned int levelnumber;
    virtual void draw( float dt);
    virtual void update( float dt);
    virtual void handleInput();
    void loadLevel();
    void loadlevelNumber();
    void checkEnd();
    GameStatePlayGame(Game* game);
};
#endif // GAME_STATE_PLAYGAME_HPP
