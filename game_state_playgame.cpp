#include <SFML/Graphics.hpp>
#include "game_state.hpp"
#include "game_state_playgame.hpp"
#include "animation_handler.hpp"
#include "player.hpp"
#include <iostream>
#include <fstream>
#include <string>


GameStatePlayGame::GameStatePlayGame(Game* game)
{

//    srand(time(NULL));
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->guiView.setSize(pos);
    this->gameView.setSize(pos);

    this->loadlevelNumber();
    this->loadLevel();
    this->gameSpeed = 1;
    this->updateWhenMove = false;

    float xM = (0.5f * ((float)(defaultWidth/pos.x)));
    float yM = (0.5f * ((float)(defaultHeight/pos.y)));
    std::cout<<"zoom: "<<((float)(defaultWidth/pos.x))<<std::endl;
    this->gameView.zoom((float)(defaultWidth/pos.x));
    this->guiView.zoom((float)(defaultWidth/pos.x));
    pos.x *= xM;
    pos.y *= yM;
    this->guiView.setCenter(pos);
    this->gameView.setCenter(pos);
}


void GameStatePlayGame::draw(float dt)
{
    dt*=gameSpeed;
    this->game->window.setView(gameView);
    this->game->window.clear(sf::Color(165,200,15));
    levelMap.draw(this->game->window,dt);

    attackList.draw(this->game->window);

    player.draw(this->game->window,dt);
    monsterManager.draw(this->game->window,dt);
    hitList.draw(this->game->window);

    if(endObiekt.objectType==5)this->game->window.draw(endObiekt.sprite);


    this->game->window.setView(guiView);
    gameGui.draw(this->game->window);
    player.hpBar.draw(this->game->window);

    return;
}

void GameStatePlayGame::update(float dt)
{
    if(updateWhenMove)
        if(!playerIsMoving) return;
    dt*=gameSpeed;
    if(player.sprite.getPosition().y > 730 || player.health<=0)this->game->popState(); //usmiercanie gdy gracz spadnie pod ekran

    attackList.update(dt); //aktualizacja wszystkich pociskow
    levelMap.update(dt); //akutlizacja elementow tla
    player.update(dt); //aktualizacja wszystkiego co zwiazane z postacia gracza
    monsterManager.update(player.sprite.getGlobalBounds().left,dt); //aktualizacja przeciwnikow
    checkEnd();
    hitList.update(dt);
    gameGui.update(gameSpeed);

    //ruch kamery za graczem
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    float xM = (0.5f * ((float)(defaultWidth/pos.x)));
    float yM = (0.5f * ((float)(defaultHeight/pos.y)));
    std::cout<<(player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width)<<" > "<<this->game->window.getSize().x*xM<<"/"<<player.sprite.getGlobalBounds().left<<" "<<this->game
    ->window.getSize().x<<std::endl;
     if(((player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width) > this->game->window.getSize().x * xM))
    {

        /*this->gameView.setCenter(sf::Vector2f(player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width*(0.5f * ((float)(defaultWidth/pos.x))),
                                    this->game->window.getSize().y*(0.5f * ((float)(defaultWidth/pos.y)))));*/
        pos.y *=yM;
        //pos.x = (player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width)*(defaultWidth/pos.x);
        pos.x = (player.sprite.getGlobalBounds().left + (player.sprite.getGlobalBounds().width));
        //pos.x +=player.sprite.getGlobalBounds().left * 0.5f;


        this->gameView.setCenter(pos);
    }

    return;
}

void GameStatePlayGame::handleInput()
{
    sf::Event event;
    sf::Vector2f mousePos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window));
    while(this->game->window.pollEvent(event))
    {
        player.turn(STAND);
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
                if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                {
                    player.turn(LEFT);
                    playerIsMoving  = true;
                }
                else if(event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                {
                    player.turn(RIGHT);
                    playerIsMoving  = true;
                }
                else if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                {
                    player.make_jump();
                    playerIsMoving  = true;
                }
                else if(event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    playerIsMoving  = true;
                    player.moveDown();
                }
                else if(event.key.code == sf::Keyboard::Space)
                {
                    player.pushAttack();
                    soundMgr.getRef("okrzyk1").play();
                    playerIsMoving  = true;
                }
                else if(event.key.code == sf::Keyboard::J)
                {
                    player.getHit(2);
                }
                else if(event.key.code == sf::Keyboard::Add)
                {
                    if(gameSpeed<2.0f)
                        gameSpeed+=0.20f;
                }
                else if(event.key.code == sf::Keyboard::Subtract)
                {
                    if(gameSpeed>0.4f)
                        gameSpeed-=0.20f;
                }
                else if(event.key.code == sf::Keyboard::F1)
                {
                    updateWhenMove = !updateWhenMove;
                }

                if(event.key.code == sf::Keyboard::Escape) this->game->popState();
                break;
            }
        case sf::Event::KeyReleased:
            {
                if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                {
                    playerIsMoving = false;
                    if(player.playerState == LEFT)
                        player.turn(STAND);
                }
                if(event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                {
                    playerIsMoving = false;
                    if(player.playerState == RIGHT)
                        player.turn(STAND);
                }
                if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::S)
                     playerIsMoving = false;
                break;
            }
        default:
            break;
        }
    }

    return;
}

void GameStatePlayGame::loadlevelNumber()
{
    std::fstream plik;
    std::string name = "data\\level\\save.dat";
    plik.open(name,std::ios::in);
    unsigned int number;
    plik>>number;
    plik.close();
    if(number<=99)
    {
        levelnumber=number;
        return;
    }
    else
    {
        plik.open(name,std::ios::out | std::ios::trunc);
        plik<<0;
        plik.close();
        levelnumber=0;
        return;
    }
}

void GameStatePlayGame::checkEnd()
{
    if(endObiekt.objectType==5)
        if(monsterManager.monsters.empty())
            if(player.sprite.getGlobalBounds().intersects(endObiekt.sprite.getGlobalBounds()))
            {
                std::cout<<"kupa";
                levelnumber++;
                std::fstream plik;
                plik.open("data\\level\\save.dat",std::ios::out | std::ios::trunc);
                plik<<levelnumber;
                plik.close();
                this->game->popState();
                this->game->pushState(new GameStatePlayGame(this->game));
//                this->game->NextLevel();
            }
}

void GameStatePlayGame::loadLevel()
{
    levelMap.attackList = &this->attackList;
    std::string nr = std::to_string(levelnumber);
    std::string tmp;
    std::fstream plik;
    std::string name = "data\\level\\textures_level_"+nr+".dat";
    plik.open(name,std::ios::in);
    name = "data\\textures\\";
    std::string cos;
    while(getline(plik,tmp))
    {
        cos=name+tmp+".png";
        texmgr.loadTexture(tmp,cos);
//        texmgr.getRef(tmp).setSmooth(true);
    }
    plik.close();

    name="data\\sounds\\";
    plik.open("data\\level\\sounds.dat",std::ios::in);
    while(getline(plik,tmp))
    {
        soundMgr.loadSound(tmp,name+tmp+".wav");
    }
    plik.close();

    name = "data\\level\\map_level_"+ nr +".dat";
    plik.open(name,std::ios::in);
    int objectnumber,x,y,width,height,animationnumber,framestart,frameend,type,variant,hp,damage;
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

        switch(type)
        {
        case 0:
            {
                levelMap.addObject(Object(sf::Vector2f((float)x,(float)y),width,height,texmgr.getRef(tmp),animations,(ObjectType)type,variant));
                break;
            }
        case 1:
            {
                levelMap.addObject(Object(sf::Vector2f((float)x,(float)y),width,height,texmgr.getRef(tmp),animations,(ObjectType)type,variant));
                levelMap.addPlatform(sf::FloatRect(sf::Vector2f(x,y),sf::Vector2f(width,height)));
                break;
            }
        case 2:
            {
                levelMap.addactiveObject(Object(sf::Vector2f((float)x,(float)y),width,height,texmgr.getRef(tmp),animations,(ObjectType)type,variant));
                break;
            }
        case 3:
            {
                levelMap.addhiddenObject(Object(sf::Vector2f((float)x,(float)y),width,height,texmgr.getRef(tmp),animations,(ObjectType)type,variant));
                break;
            }
        case 4:
            {
                plik>>hp; plik>>damage;
                levelMap.addtrapObject(ObjectTrap(sf::Vector2f((float)x,(float)y),width,height,texmgr.getRef(tmp),animations,(ObjectType)type,variant,hp,damage));
                break;
            }
        case 5:
            {
                endObiekt = Object(sf::Vector2f((float)x,(float)y),width,height,texmgr.getRef(tmp),animations,(ObjectType)type,variant);
                break;
            }
        }//switch end
    }//koniec petli wczytujacej
    plik.close();

    player.load(nr,texmgr,&levelMap,&attackList,&hitList,soundMgr);
    monsterManager.load(nr,texmgr,&levelMap,&attackList,&hitList);
    gameGui.load(this->levelnumber,&monsterManager,texmgr);
    levelMap.hitList = &hitList;
}
