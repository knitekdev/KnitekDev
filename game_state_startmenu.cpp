#include <SFML/Graphics.hpp>

#include "game_state_startmenu.hpp"
#include "game_state_playgame.hpp"
#include "game_state.hpp"
#include "menu_gui.hpp"
extern otwieranie_linku(const char ser[]);


GameStateStartMenu::GameStateStartMenu(Game* game)
{
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
    guiMenu.start(this->game->window);
}

void GameStateStartMenu::draw(const float dt)
{
    this->game->window.setView(this->view);
    this->game->window.clear(sf::Color::Black);
    this->game->window.draw(this->game->background);
    this->game->window.draw(guiMenu);

    return;
}

void GameStateStartMenu::update(const float dt)
{
    return;
}

void GameStateStartMenu::handleInput()
{
    sf::Event event;

    while(this->game->window.pollEvent(event))
    {
        sf::Vector2f mousePos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window));
        switch(event.type)
        {
        case sf::Event::Closed:
            {
                game->window.close();
                break;
            }
        /*case sf::Event::Resized:
            {
                this->view.setSize(event.size.width, event.size.height);
                this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0)));
                this->game->background.setScale(
                    float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
                    float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
                break;
            }*/
        case sf::Event::KeyPressed:
            {
                if(event.key.code == sf::Keyboard::Escape) this->game->window.close();
//                else if(event.key.code == sf::Keyboard::Space) this->loadgame();
                break;
            }
        case sf::Event::MouseMoved:
            {
                this->guiMenu.check(mousePos);
                break;
            }
        case sf::Event::MouseButtonPressed:
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {

                    std::string message = this->guiMenu.check(mousePos);

                    if(message == "new_game") this->loadgame(message);
                    else if(message == "continue") this->loadgame(message);
                    else if(message == "authors" ){this->guiMenu.authors= this->guiMenu.authors ? false : true; break;}
                    else if(message == "exit") this->game->window.close();
                    else if(message == "donate")    otwieranie_linku(guiMenu.addres.c_str());
                    this->guiMenu.authors = false;
                }
                break;
            }
        default:
            break;
        }
    }

    return;
}

void GameStateStartMenu::loadgame(std::string msg)
{

    if(msg=="new_game")
    {
        std::fstream plik;
        plik.open("data\\level\\save.dat",std::ios::out | std::ios::trunc);
        plik<<0;
        plik.close();
    }
    this->game->pushState(new GameStatePlayGame(this->game));
    return;
}
