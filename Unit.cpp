//
// Created by Nikita on 28.05.2026.
//

#include "Unit.h"
#include "Game.h"

#include "Tile.h"


Unit::Unit(std::string name, int x, int y, int maxHealth, int damage, int maxMovement, int range, UnitType type, int cost,
           std::map<Resource, int> requiredResources, Building* requiredBuilding) {
    this->name = name;
    this->x = x;
    this->y = y;
    this->maxHealth = maxHealth;
    this->health = maxHealth;
    this->damage = damage;
    this->maxMovement = maxMovement;
    this->movement = maxMovement;
    this->range = range;
    this->cost = cost;
    this->type = type;
    this->requiredResources = requiredResources;
    this->requiredBuilding = requiredBuilding;
}

std::string const Unit::getName() {
    return name;
}
int const Unit::getX() {
    return x;
}
int const Unit::getY() {
    return y;
}
int const Unit::getMaxHealth() {
    return maxHealth;
}
int const Unit::getHealth() {
    return health;
}
int const Unit::getDamage() {
    return damage;
}
int const Unit::getMaxMovement() {
    return maxMovement;
}
int const Unit::getMovement() {
    return movement;
}
int const Unit::getRange() {
    return range;
}
int const Unit::getCost() {
    return cost;
}
UnitType const Unit::getType() {
    return type;
}
std::map<Resource, int> const Unit::getRequiredResources() {
    return requiredResources;
}
Building* const Unit::getRequiredBuilding() {
    return requiredBuilding;
}

void Unit::move(int x, int y, Game* game) {
    int distance =
        std::abs(x - this->x) +
        std::abs(y - this->y);

    if (distance != 1)
        return;

    Tile* tile = game->getTile(x, y);

    if (!tile)
        return;

    int movementCost = tile->getMovementCost(this->type);
    if (movementCost < 0)
        return;
    if (this->movement < movementCost)
        return;

    this->movement -= movementCost;
    this->x = x;
    this->y = y;
}

void Unit::takeDamage(int hp) {
    this->health -= hp;
    if (health <= 0) {
        delete this;
    }
}

void Unit::attack(int x, int y, Game* game) {
    if (std::abs(x - this->x) + std::abs(y - this->y) <= range) {
        Unit* enemy = game->getTile(x, y)->getUnit();
        if (enemy) {
            enemy->takeDamage(this->damage);
        }
    }
}

// TODO: Сделать метод upgrade