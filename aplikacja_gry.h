#pragma once
#include "menu.h" 
#include "GameState.h" 
#include <iostream>
#include <vector>
enum class GameState { Menu, Playing, Paused, Exiting };

class GameApplication {
private:
    sf::RenderWindow window;
    Game game;
    GameState currentState;
    Menu menu;
    sf::Font font;
    sf::Text pauseText;
    
    void initialize() {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Błąd ładowania czcionki 'arial.ttf'. Upewnij się, że plik jest dostępny." << std::endl;
        }

        pauseText.setFont(font);
        pauseText.setString("PAUZA");
        pauseText.setCharacterSize(50);
        pauseText.setFillColor(sf::Color::Black);
        pauseText.setPosition(325, 350);
    }
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                currentState = GameState::Exiting;
            }
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentState == GameState::Menu) {
                menu.update(event); 
            } else if (currentState == GameState::Playing) {
                game.handleInput(event); 
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                    GameStatee gs(game.getPaletka(), game.getPilka(), game.getCegly(), game.getDx(), game.getDy());
                    gs.saveToFile("save.txt");
                    currentState = GameState::Paused;
                }
            } else if (currentState == GameState::Paused) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                    GameStatee gs(game.getPaletka(), game.getPilka(), game.getCegly(), game.getDx(), game.getDy());
                    if (gs.loadFromFile("save.txt")) {
                        game.setPaletkaPos(gs.getPaletkaPos());
                        game.setPilkaPos(gs.getPilkaPos());
                        game.setDx(gs.getPredkoscX());
                        game.setDy(gs.getPredkoscY());
                        
                        std::vector<cegielka> nowe;
                        for (const auto& bd : gs.getCegly()) {
                            nowe.emplace_back(bd.x, bd.y, bd.hp);
                        }
                        game.setCegly(nowe);

                        currentState = GameState::Playing;
                    }
                }
            }
        }
    }

    void render() {
        window.clear(sf::Color(245, 245, 220)); 

        if (currentState == GameState::Menu) {
            menu.draw(window);
            if (menu.startGameSelected())
                currentState = GameState::Playing;
        } else if (currentState == GameState::Playing) {
            game.update(window); 
            game.render(window); 
        } else if (currentState == GameState::Paused) {
            game.render(window);
            window.draw(pauseText);
        } else if (currentState == GameState::Exiting) {
            window.close();
        }

        window.display();
    }

public:
    GameApplication() 
        : window(sf::VideoMode(800, 600), "Giereczka"), 
          currentState(GameState::Menu),
          menu(800, 600) 
    {
        initialize();
    }


    void run() {
        while (window.isOpen()) {
            handleEvents(); 
            render();       
        }
    }
};

