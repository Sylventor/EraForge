//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_UNIT_H
#define UNTITLED_UNIT_H
#include <map>
#include <string>

#include "Game.h"
#include "Globals.h"

class Building;
class Civilization;

class Unit {
private:
    std::string name;
    int x;
    int y;
    int health;
    int maxHealth;
    int damage;
    int movement;
    int maxMovement;
    int range;
    int cost;
    UnitType type;
    std::map<Resource, int> requiredResources;
    Building* requiredBuilding;
public:
    Unit(std::string name, int x, int y, int maxHealth, int damage, int maxMovement, int range, UnitType type, int cost,
         std::map<Resource, int> requiredResources, Building* requiredBuilding);

    std::string const getName();
    int const getX();
    int const getY();
    int const getHealth();
    int const getMaxHealth();
    int const getDamage();
    int const getMovement();
    int const getMaxMovement();
    int const getRange();
    int const getMaxRange();
    int const getCost();
    UnitType const getType();
    std::map<Resource, int> const getRequiredResources();
    Building* const getRequiredBuilding();

    void move(int x, int y);
    void attack(int x, int y, Game* game);
    void upgrade();
    void takeDamage(int hp);
};


#endif //UNTITLED_UNIT_H
