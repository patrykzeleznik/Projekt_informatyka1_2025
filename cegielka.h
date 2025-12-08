#pragma once
#include <array>
#include <SFML/Graphics.hpp>

class cegielka{
private:
    sf::RectangleShape cegla;
    sf::Vector2f position;
    float pktZycia;
    bool JestZniszczony;
    static const std::array<sf::Color, 3> kolory;
public:
    cegielka(int x, int y,int L);
    void rysuj(sf::RenderWindow& window);
    void trafienie();
    void aktualizujkolor();
    sf::Vector2f getPos() const {return cegla.getPosition();};
    bool getJestZniszczony(){return JestZniszczony;};
    int getPktZycia() const {return pktZycia;};
};

cegielka::cegielka(int x, int y, int L){
    pktZycia = L;
    JestZniszczony = false;
    cegla.setSize({50,20});
    cegla.setOrigin(25,10);
    cegla.setPosition(x,y);
    cegla.setOutlineThickness(2);
    cegla.setOutlineColor(sf::Color::Black); 
     aktualizujkolor();
}

const std::array<sf::Color, 3> cegielka::kolory = {
    sf::Color::Black,
    sf::Color::Magenta,
    sf::Color::White
};

void cegielka::aktualizujkolor(){
    if(pktZycia >= 1 && pktZycia <= 3)
        cegla.setFillColor(kolory[pktZycia - 1]);
}

void cegielka::trafienie(){
    if(JestZniszczony==true)
        return;
    pktZycia--;
    aktualizujkolor();
    if(pktZycia<=0)
        JestZniszczony=true;
}

void cegielka::rysuj(sf::RenderWindow& window){
    window.draw(cegla);
}