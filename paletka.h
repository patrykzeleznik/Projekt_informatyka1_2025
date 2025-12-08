#pragma once
#include <SFML/Graphics.hpp>

class Paletka{
private:
    sf::RectangleShape paletka;
    sf::Vector2f position;
public:
    Paletka();
    void ruch(sf::Event event, sf::Clock& zegar);
    void rysuj(sf::RenderWindow& window);
    sf::Vector2f getPos() const;
    void setPos(sf::Vector2f pos);
};

Paletka::Paletka(){
    paletka.setSize({100,10});
    paletka.setOrigin(50,5);
    paletka.setPosition(400,550);
    paletka.setFillColor(sf::Color::Green);
    paletka.setOutlineThickness(3);
    paletka.setOutlineColor(sf::Color::Black);
}

void Paletka::ruch(sf::Event event, sf::Clock& zegar){
    sf::Vector2f pos = paletka.getPosition();
    if(zegar.getElapsedTime().asMicroseconds()>10.0f){
        if(event.key.code == sf::Keyboard::A)
            if(pos.x - 50 >= 0)
            paletka.move(-20,0);
            else
            paletka.move(0,0);
        if(event.key.code == sf::Keyboard::D)
            if(pos.x + 50 <= 800)
            paletka.move(20,0);
            else
            paletka.move(0,0);
    }
    zegar.restart();
}

sf::Vector2f Paletka::getPos() const {return paletka.getPosition();};

void Paletka::rysuj(sf::RenderWindow& window){
    window.draw(paletka);
}

void Paletka::setPos(sf::Vector2f pos) {
    position = pos;
    paletka.setPosition(position);
}