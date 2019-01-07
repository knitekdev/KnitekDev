#ifndef TESTING_TOOL_HPP
#define TESTING_TOOL_HPP
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>

#define tools_length 3

class Testing_Tool
{
    public:

        Testing_Tool();
        Testing_Tool(sf::Font &font);
        virtual ~Testing_Tool();

        void update(std::string tab[tools_length]);
        void draw(sf::RenderWindow &window);
    protected:
    private:
        std::string headers[tools_length];
        sf::Text texts[tools_length];
        sf::Font font;
};

#endif // TESTING_TOOL_HPP
