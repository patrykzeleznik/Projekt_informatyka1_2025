#pragma once
#include <SFML/Graphics.hpp>

class Menu{
private:
    sf::Font font;
    sf::Text text;
    bool startGame = false;
public:
        Menu(float width, float height);

        void draw(sf::RenderWindow& window);
        void update(const sf::Event& event);
        bool startGameSelected() const { return startGame; }
};

Menu::Menu(float width, float height)
{
    font.loadFromFile("arial.ttf");   
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString("Nacisnij ENTER, aby zaczac");
    text.setCharacterSize(30);
    text.setPosition(width / 2 - 200, height / 2);
}

void Menu::update(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Enter)
    {
        startGame = true;
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(text);
}