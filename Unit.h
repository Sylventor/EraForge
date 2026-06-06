//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_UNIT_H
#define UNTITLED_UNIT_H
#include <map>
#include <string>
#include "Globals.h"

class Building{};

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
    UnitType type;
    std::map<Resource, int> requiredResources;
    Building requiredBuilding;
public:
    Unit();

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
    UnitType const getType();
    std::map<Resource, int> const getRequiredResources();
    Building const getRequiredBuilding();

    void move(int x, int y);
    void attack(int x, int y);
    void upgrade();
    void takeDamage(int hp);
};


#endif //UNTITLED_UNIT_H
