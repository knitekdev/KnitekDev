#include <SFML/Graphics.hpp>

#include "game_state.hpp"
#include "game_state_playgame.hpp"
#include "animation_handler.hpp"
#include "player.hpp"
#include <iostream>
#include <fstream>
#include <string>
//#include <cstdlib>

GameStatePlayGame::GameStatePlayGame(Game* game)
{

//    srand(time(NULL));
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->guiView.setSize(pos);
    this->gameView.setSize(pos);
    pos *= 0.5f;
    this->guiView.setCenter(pos);
    this->gameView.setCenter(pos);
    this->loadTextures();
    this->loadLevel(1);
}

void GameStatePlayGame::loadTextures()
{
}

void GameStatePlayGame::draw(const float dt)
{
    this->game->window.setView(gameView);
    this->game->window.clear(sf::Color(165,200,15));
    levelMap.draw(this->game->window,dt);

    attackList.draw(this->game->window);

    player.draw(this->game->window,dt);
    monsterManager.draw(this->game->window,dt);

    this->game->window.setView(guiView);
    player.hpBar.draw(this->game->window);


    return;
}

void GameStatePlayGame::update(const float dt)
{
    if(player.sprite.getPosition().y > 730 || player.health<=0)this->game->popState(); //usmiercanie gdy gracz spadnie pod ekran

    attackList.update(dt); //aktualizacja wszystkich pociskow
    levelMap.update(dt);
    player.update(dt);
    monsterManager.update(player.sprite.getGlobalBounds().left,dt);


    //ruch kamery za graczem
    if((player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width/2 > this->game->window.getSize().x / 2) &&
        (player.sprite.getGlobalBounds().left < 5000))
    this->gameView.setCenter(sf::Vector2f(player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width/2,
                                    this->game->window.getSize().y/2));
    return;
}

void GameStatePlayGame::handleInput()
{
    sf::Event event;
    sf::Vector2f mousePos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window));
    while(this->game->window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            {
                this->game->window.close();
                break;
            }
//        case sf::Event::Resized:
//            {
//                gameView.setSize(event.size.width, event.size.height);
//                guiView.setSize(event.size.width, event.size.height);
//                this->game->background.setPosition(
//                    this->game->window.mapPixelToCoords(sf::Vector2i(0,0), this->guiView));
//                this->game->background.setScale(
//                    float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
//                    float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
//                break;
//            }
        case sf::Event::KeyPressed:
            {
                if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) player.turn(LEFT);
                else if(event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) player.turn(RIGHT);
                else if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) player.jump();
                else if(event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) player.sprite.move(0,1);
                else if(event.key.code == sf::Keyboard::Space) attackList.addAttack(player.pushAttack());
                else if(event.key.code == sf::Keyboard::J) player.getHit(2);

                if(event.key.code == sf::Keyboard::Escape) this->game->popState();
                break;
            }
        case sf::Event::KeyReleased:
            {
                if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) if(player.playerState == LEFT) player.turn(STAND);
                if(event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) if(player.playerState == RIGHT) player.turn(STAND);
                break;
            }
        default:
            break;
        }
    }

    return;
}

void GameStatePlayGame::loadLevel(const unsigned int number)
{
    std::string nr = std::to_string(number);
    std::string tmp;
    std::fstream plik;
    std::string name = "data\\level\\textures_level_"+nr+".dat";
    plik.open(name,std::ios::in);
    name = "data\\textures\\level"+nr+"\\";
    std::string cos;
    while(getline(plik,tmp))
    {
        cos=name+tmp+".png";
        texmgr.loadTexture(tmp,cos);
    }
    plik.close();

    name = "data\\level\\map_level_"+ nr +".dat";
    plik.open(name,std::ios::in);
    int objectnumber,x,y,width,height,animationnumber,framestart,frameend,type,variant;

    float duration;
    plik>>objectnumber;
    for(int i = 0; i<objectnumber; i++)
    {
        plik>>x;
        plik>>y;
        plik>>width;
        plik>>height;
        plik>>tmp;
        plik>>animationnumber;
        std::vector<Animation> animations;
        for(int j=0; j<animationnumber; j++)
        {
            plik>>framestart;
            plik>>frameend;
            plik>>duration;
            animations.push_back(Animation(framestart,frameend,duration));
        }
        if(animationnumber == 0)animations.push_back(Animation(0,0,1.0f));
        plik>>type;
        plik>>variant;
        levelMap.addObject(Object(sf::Vector2f((float)x,(float)y),width,height,texmgr.getRef(tmp),animations,(ObjectType)type,variant));
        if(type==PLATFORM)levelMap.addPlatform(sf::FloatRect(sf::Vector2f(x,y),sf::Vector2f(width,height)));
    }
    plik.close();

    player.load(nr,texmgr,&levelMap,&attackList);
    monsterManager.load(nr,texmgr,&levelMap,&attackList);

}
