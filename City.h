//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_CITY_H
#define UNTITLED_CITY_H
#include <string>
#include <vector>

class Civilization{};
class Tile{};

class City {
private:
    std::vector<Tile*> ownedTiles;
    std::string name;
    Civilization* owner;
    int population;
    int food;
    int health;
    int maxHealth;
    int x;
    int y;
public:
    City(std::vector<Tile*> ownedTiles, Civilization* owner, int x, int y, std::string name);
    void upgrade();
    void update();
};


#endif //UNTITLED_CITY_H
