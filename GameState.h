#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "game.h"
#include <fstream>

struct BlockData{
    int x,y;
    int hp;
};

class GameStatee {
private:
    sf::Vector2f PozycjaPilki;
    sf::Vector2f PozycjaPaletki;
    int PredkoscPilkiX;
    int PredkoscPilkiY;
    std::vector<BlockData> ceglyy;
public:
    GameStatee(const Paletka& p1, const Pilka& p2, const std::vector<cegielka>& cegly, float dx, float dy);
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    sf::Vector2f getPaletkaPos() const { return PozycjaPaletki; }
    sf::Vector2f getPilkaPos() const { return PozycjaPilki; }
    float getPredkoscX() const { return PredkoscPilkiX; }
    float getPredkoscY() const { return PredkoscPilkiY; }
    const std::vector<BlockData>& getCegly() const { return ceglyy; }
};

GameStatee::GameStatee(const Paletka& p1, const Pilka& p2, const std::vector<cegielka>& cegly, float dx, float dy)
    : PozycjaPilki(p2.getPos()),
      PozycjaPaletki(p1.getPos()),
      PredkoscPilkiX(dx),
      PredkoscPilkiY(dy)
{
    for (const auto& cegla : cegly) {
        BlockData bd;
        bd.x = cegla.getPos().x;
        bd.y = cegla.getPos().y;
        bd.hp = cegla.getPktZycia();
        ceglyy.push_back(bd);
    }
}

bool GameStatee::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << PozycjaPaletki.x << " " << PozycjaPaletki.y << "\n";

    file << PozycjaPilki.x << " " << PozycjaPilki.y << " " << PredkoscPilkiX << " " << PredkoscPilkiY << "\n";

    file << ceglyy.size() << "\n";
    for (const auto& bd : ceglyy) {
        file << bd.x << " " << bd.y << " " << bd.hp << "\n";
    }
    file.close();
    return true;
}

bool GameStatee::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    file >> PozycjaPaletki.x >> PozycjaPaletki.y;
    file >> PozycjaPilki.x >> PozycjaPilki.y >> PredkoscPilkiX >> PredkoscPilkiY;
    
    size_t ceglyCount;
    file >> ceglyCount;
    ceglyy.clear();
    for (size_t i = 0; i < ceglyCount; i++) {
        BlockData bd;
        file >> bd.x >> bd.y >> bd.hp;
        ceglyy.push_back(bd);
    }
    file.close();
    return true;
}

    