#ifndef MENU_GUI_HPP
#define MENU_GUI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Button
{
public:
    sf::Text text;
    sf::RectangleShape shape;
    std::string message;
    Button(sf::Text& text, sf::RectangleShape& shape, std::string& message);

    sf::Text getButton(){return text;}
};

class GuiMenu : public sf::Transformable, public sf::Drawable
{
public:
    sf::Font font;
    std::vector<Button> buttons;

    void start(sf::RenderWindow& window);

    std::string check(const sf::Vector2f mousePos);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
#endif // MENU_GUI_HPP
