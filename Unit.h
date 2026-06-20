//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_UNIT_H
#define UNTITLED_UNIT_H
#include <map>
#include <string>

#include "Types.h"

class Game;
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
    int researchCost;
    UnitType type;
    std::map<Resource, int> requiredResources;
    Building* requiredBuilding;
public:
    Unit(std::string name, int x, int y, int maxHealth, int damage, int maxMovement, int range, UnitType type, int cost, int researchCost,
         std::map<Resource, int> requiredResources, Building* requiredBuilding);

    Unit(const Unit &unit);

    Unit(const Unit &unit, int x, int y, Game* game);

    std::string getName() const;
    int getX() const;
    int getY() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getDamage() const;
    int getMovement() const;
    int getMaxMovement() const;
    int getRange() const;
    int getCost() const;
    int getResearchCost() const;
    UnitType getType() const;
    std::map<Resource, int> getRequiredResources() const;
    Building* getRequiredBuilding() const;

    int move(int x, int y, Game* game);
    void attack(int x, int y, Game* game);
    void update(Game* game);
    void takeDamage(int hp);
    void heal(int hp);
    void revealMap(Game* game);
};


#endif //UNTITLED_UNIT_H
