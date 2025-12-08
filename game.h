#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "cegielka.h"
#include "pilka.h"

class Game{
private:
    sf::Clock zegar;
    sf::Event event;
    Paletka p1;
    Pilka p2;
    std::vector<cegielka> cegly;
    float dx = 1;
    float dy = 1;
public:
    Game();
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void handleInput(const sf::Event& event);
    const Pilka& getPilka() const { return p2; }
    const Paletka& getPaletka() const { return p1; }
    const std::vector<cegielka>& getCegly() const { return cegly; }
    float getDx() const { return dx; }
    float getDy() const { return dy; }
    void setDx(float newDx) { dx = newDx; }
    void setDy(float newDy) { dy = newDy; }
    void setPilkaPos(sf::Vector2f pos) { p2.setPos(pos); }
    void setPaletkaPos(sf::Vector2f pos) { p1.setPos(pos); }
    void setCegly(const std::vector<cegielka>& newCegly) { cegly = newCegly; }
};

Game::Game()
{
    for(int y=0;y<7;y++)
    for(int x=0;x<6;x++)
    {
        cegly.emplace_back(100 + x*125, 50 + y*35, 3);
    }
}

void Game::handleInput(const sf::Event& event) {
    
    p1.ruch(event, zegar);
   
}

void Game::update(sf::RenderWindow& window) {
    p2.kolizja(zegar, dx, dy, window, p1, p2);
    for (int i = 0; i < cegly.size(); i++) {
        if (p2.getPos().y - 20 <= cegly[i].getPos().y + 10 && p2.getPos().y + 20 >= cegly[i].getPos().y - 10 && p2.getPos().x + 20 >= cegly[i].getPos().x - 25 && p2.getPos().x - 20 <= cegly[i].getPos().x + 25) {

            float diffX = p2.getPos().x - cegly[i].getPos().x;
            float diffY = p2.getPos().y - cegly[i].getPos().y;

            if (std::abs(diffX) > std::abs(diffY)) {

                dx = -dx;
                p2.przesun(dx > 0 ? 10 : -10, 0);

            }
            else {

                dy = -dy;
                p2.przesun(0, dy > 0 ? 10 : -10);
            }

            cegly[i].trafienie();
            if (cegly[i].getJestZniszczony()) {
                cegly.erase(cegly.begin() + i);
            }
            break;

        }
    }
}

void Game::render(sf::RenderWindow& window) {
    for (auto& cegla : cegly) {
        cegla.rysuj(window);
    }
    window.draw(p2.getPilka());
    p1.rysuj(window);
}