//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_CITY_H
#define UNTITLED_CITY_H
#include <string>
#include <vector>

class Civilization;
class Tile;
class Game;

class City {
private:
    std::vector<Tile*> ownedTiles;
    std::string name;
    Civilization* owner;
    int population;
    int populationForUpgrade;
    int food;
    int health;
    int maxHealth;
    int x;
    int y;
public:
    City(Game* game, Civilization* owner, int x, int y, std::string name);

    std::vector<Tile*> const getOwnedTiles();
    std::string const getName();
    Civilization* const getOwner();
    int const getPopulation();
    int const getFood();
    int const getHealth();
    int const getMaxHealth();
    int const getX();
    int const getY();

    void takeDamage(int damage);
    void repair(int health);

    void upgrade();
    void update();
};


#endif //UNTITLED_CITY_H
