#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.hpp"
#include "game_state.hpp"
#include "texture_manager.hpp"//-Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic


Game::Game()
{
    this->loadTextures();

    this->window.create(sf::VideoMode(1280,720), "Korek Sewer Worker",sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(40);

    this->background.setTexture(this->texmgr.getRef("background"));
}

void Game::loadTextures()
{
    texmgr.loadTexture("background","data\\textures\\background.png");
}

void Game::NextLevel()
{

}

void Game::pushState(GameState* state)
{
    this->states.push(state);
    return;
}

void Game::popState()
{
//    delete this->states.top();
    this->states.pop();
    return;
}

void Game::changeState(GameState* state)
{
    if(!this->states.empty())
        popState();
    pushState(state);
}

GameState* Game::peekState()
{
    if(this->states.empty()) return nullptr;
    return this->states.top();
}

void Game::gameLoop()
{
    sf::Clock clock;

    while(this->window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        if(peekState() == nullptr) continue;
        peekState()->handleInput();
        peekState()->update(dt);
        this->window.clear(sf::Color::Black);
        peekState()->draw(dt);
        this->window.display();
    }
}

Game::~Game()
{
    while(!this->states.empty()) popState();
}
