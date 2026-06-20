//
// Created by Nikita on 28.05.2026.
//

#include "Unit.h"
#include "Game.h"
#include "Civilization.h"
#include "Tile.h"


Unit::Unit(std::string name, int x, int y, int maxHealth, int damage, int maxMovement, int range, UnitType type, int cost, int researchCost,
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
    this->researchCost = researchCost;
    this->type = type;
    this->requiredResources = requiredResources;
    this->requiredBuilding = requiredBuilding;
}

Unit::Unit(const Unit &unit) : name(unit.name), x(unit.x), y(unit.y), maxHealth(unit.maxHealth), health(unit.maxHealth),
                               damage(unit.damage), maxMovement(unit.maxMovement), movement(unit.maxMovement),
                               range(unit.range), cost(unit.cost), researchCost(unit.researchCost), type(unit.type), requiredResources(unit.requiredResources),
                               requiredBuilding(unit.requiredBuilding) {}

Unit::Unit(const Unit &unit, int x, int y, Game* game) : name(unit.name), x(x), y(y), maxHealth(unit.maxHealth), health(unit.maxHealth),
                                                   damage(unit.damage), maxMovement(unit.maxMovement), movement(unit.maxMovement),
                                                   range(unit.range), cost(unit.cost), researchCost(unit.researchCost), type(unit.type), requiredResources(unit.requiredResources),
                                                   requiredBuilding(unit.requiredBuilding) {
    game->getTile(x, y)->setUnit(this);
    this->revealMap(game);
    game->getPlayer()->addUnit(this);
}

Unit::Unit(const Unit* unit, int x, int y, Game* game) : name(unit->name), x(x), y(y), maxHealth(unit->maxHealth), health(unit->maxHealth),
                                                   damage(unit->damage), maxMovement(unit->maxMovement), movement(unit->maxMovement),
                                                   range(unit->range), cost(unit->cost), researchCost(unit->researchCost), type(unit->type), requiredResources(unit->requiredResources),
                                                   requiredBuilding(unit->requiredBuilding) {
    game->getTile(x, y)->setUnit(this);
    this->revealMap(game);
    game->getPlayer()->addUnit(this);
}

std::string Unit::getName() const{
    return name;
}
int Unit::getX() const{
    return x;
}
int Unit::getY() const{
    return y;
}
int Unit::getMaxHealth() const{
    return maxHealth;
}
int Unit::getHealth() const{
    return health;
}
int Unit::getDamage() const{
    return damage;
}
int Unit::getMaxMovement() const{
    return maxMovement;
}
int Unit::getMovement() const{
    return movement;
}
int Unit::getRange() const{
    return range;
}
int Unit::getCost() const{
    return cost;
}
int Unit::getResearchCost() const {
    return researchCost;
}
UnitType Unit::getType() const{
    return type;
}
std::map<Resource, int> Unit::getRequiredResources() const{
    return requiredResources;
}
Building* Unit::getRequiredBuilding() const{
    return requiredBuilding;
}

int Unit::move(int x, int y, Game* game) {
    int distance =
        std::abs(x - this->x) +
        std::abs(y - this->y);

    if (distance != 1)
        return -6; // Returns -6 if distance is too big

    Tile* tile = game->getTile(x, y);

    if (!tile)
        return -7; // Returns -7 if it can't find tile at this coordinates

    int movementCost = tile->getMovementCost(this->type);
    if (movementCost < 0)
        return movementCost; // Returns number from -4 to -1
    if (this->movement < movementCost)
        return -8; // Returns -8 if not enough movement points

    game->getTile(this->x, this->y)->setUnit(nullptr);
    this->movement -= movementCost;
    this->x = x;
    this->y = y;
    tile->setUnit(this);
    revealMap(game);
    return 1;
}

void Unit::takeDamage(int hp) {
    this->health -= hp;
    if (health <= 0) {
        delete this;
    }
}

void Unit::heal(int hp) {
    this->health += hp;
    if (this->health > this->maxHealth) {
        this->health = this->maxHealth;
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

void Unit::revealMap(Game *game) {
    for (int nx = -2; nx <= 2; nx++) {
        for (int ny = -2; ny <= 2; ny++) {
            if (this->x+nx >= 0 && this->x+nx < MAP_SIZE_X && this->y+ny >= 0 && this->y+ny < MAP_SIZE_Y) {
                Tile* t = game->getTile(x+nx, y+ny);
                t->setRevealed(true);
            }
        }
    }
}


void Unit::update(Game* game) {
    this->movement = this->maxMovement;
    if (game->getTile(this->x, this->y)->getOwner() != nullptr) {
        this->heal(10);
    }
}
