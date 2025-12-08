#include <SFML/Graphics.hpp>
#include "menu.h"
#include "GameState.h"
#include <iostream>

enum class GameState { Menu, Playing, Paused, Exiting };

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Giereczka");
    Game game;
    GameState currentState = GameState::Menu;
    Menu menu(800, 600);
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text pauseText;
    pauseText.setFont(font);
    pauseText.setString("PAUZA");
    pauseText.setCharacterSize(50);
    pauseText.setFillColor(sf::Color::Black);
    pauseText.setPosition(325, 350);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            currentState = GameState::Exiting;
            }   
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentState == GameState::Menu)
                menu.update(event); 
            else if (currentState == GameState::Playing) {
                game.handleInput(event); 
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
                GameStatee gs(game.getPaletka(), game.getPilka(), game.getCegly(), game.getDx(), game.getDy());
                gs.saveToFile("save.txt");
                currentState = GameState::Paused;
                }
            }
            else if (currentState == GameState::Paused) {
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
                    GameStatee gs(game.getPaletka(), game.getPilka(), game.getCegly(), game.getDx(), game.getDy());
                    if(gs.loadFromFile("save.txt")) {
                        game.setPaletkaPos(gs.getPaletkaPos());
                        game.setPilkaPos(gs.getPilkaPos());
                        game.setDx(gs.getPredkoscX());
                        game.setDy(gs.getPredkoscY());
                        std::vector<cegielka> nowe;
                        for(const auto& bd : gs.getCegly()){
                        nowe.emplace_back(bd.x, bd.y, bd.hp);
                        }
                        game.setCegly(nowe);

                        currentState = GameState::Playing;
                    }
                }
            }
        }
    
        window.clear(sf::Color(245, 245, 220));

        if (currentState == GameState::Menu)
            {
                menu.draw(window);

                if (menu.startGameSelected())
                    currentState = GameState::Playing;
            }
            else if (currentState == GameState::Playing)
            {
                game.update(window);
                game.render(window);
            }

            else if (currentState == GameState::Paused){
            game.render(window);     
            window.draw(pauseText);  
            }
            else if (currentState == GameState::Exiting)
            {
                window.close();
            }

        window.display();
    }
    return 0;
}