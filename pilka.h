#pragma once
#include <SFML/Graphics.hpp>
#include "paletka.h"

class Pilka{
private:
    sf::Vector2f position;
    sf::CircleShape pilka;
    bool koniecgry = false;
public:
    Pilka();
    void przesun(float x_in, float y_in);
    void kolizja(sf::Clock& zegar, float& dx, float& dy, sf::RenderWindow& window, Paletka& p1, Pilka& p2);
    sf::CircleShape getPilka(){return pilka;};
    sf::Vector2f getPos() const {return pilka.getPosition();};
    void setPos(sf::Vector2f pos);
};

Pilka::Pilka(){
    pilka.setPosition(100,300);
    pilka.setOrigin(20,20);
    pilka.setRadius(20);
    pilka.setFillColor(sf::Color::Green);
    pilka.setOutlineThickness(3);
    pilka.setOutlineColor(sf::Color::Black);
}

void Pilka::przesun(float x_in, float y_in){
    sf::Vector2f pos;
    pos.x = x_in;
    pos.y = y_in;
    pilka.move(pos);
}

void Pilka::kolizja(sf::Clock& zegar, float& dx, float& dy, sf::RenderWindow& window, Paletka& p1, Pilka& p2){
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text Text;
    sf::Text TText;
    Text.setFont(font);
    TText.setFont(font);
    Text.setString("GAME OVER");
    TText.setString("kliknij ESC, aby wyjsc");
    Text.setCharacterSize(50);
    TText.setCharacterSize(20);
    Text.setFillColor(sf::Color::Black);
    TText.setFillColor(sf::Color::Black);
    Text.setPosition(250, 350);
    TText.setPosition(300, 400);
    if (koniecgry){
            window.draw(Text);
            window.draw(TText);
            return;
        }
    if(zegar.getElapsedTime().asMilliseconds()>3.0f){
            if(p2.getPos().y + 20 == window.getSize().y){
                dx = 0;
                dy = 0;
                koniecgry = true;
            }
            else{
                if(p2.getPos().x + 20 >= window.getSize().x || p2.getPos().x - 20  <= 0)
                    dx = -dx;
                if(p2.getPos().y + 20  >= p1.getPos().y - 5 && p2.getPos().y - 20 <= p1.getPos().y + 5 && p2.getPos().x + 20 >= p1.getPos().x - 50 && p2.getPos().x - 20 <= p1.getPos().x + 50){
                    if(p2.getPos().y -20 < p1.getPos().y + 5 && p2.getPos().y + 20 > p1.getPos().y - 5){
                        dx = -dx;
                        dy = -dy;
                    }
                    else
                        dy = -dy; 
                }
                if(p2.getPos().y + 20 >= window.getSize().y || p2.getPos().y - 20 <= 0)
                    dy = -dy;
            }
            p2.przesun(dx,dy);
            zegar.restart();
        }
        if (koniecgry){
            window.draw(Text);
            window.draw(TText);
        }
}

void Pilka::setPos(sf::Vector2f pos) {
    position = pos;
    pilka.setPosition(position);
}