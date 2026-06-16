//
// Created by Nikita on 28.05.2026.
//

#include "City.h"

#include "Building.h"
#include "Tile.h"
#include "Civilization.h"
#include "Game.h"

City::City(Game* game, Civilization* owner, int x, int y, std::string name) {
    this->owner = owner;
    this->x = x;
    this->y = y;
    this->name = name;
    int population = 3;
    int populationForUpgrade = 6;
    int food = 3;
    int maxHealth = 300;
    int health = maxHealth;
    for (int nx = -2; nx <= 2; nx++) {
        for (int ny = -2; ny <= 2; ny++) {
            if (x+nx > 0 || x+nx < MAP_SIZE_X || y+ny > 0 || y+ny < MAP_SIZE_Y) {
               Tile* t = game->getTile(x+nx, y+ny);
               ownedTiles.push_back(t);
               t->setOwner(this);
               t->setRevealed(true);
            }
        }
    }
    game->getTile(x, y)->setBuilding(new Building(b_city));
}

std::vector<Tile*> const City::getOwnedTiles() {
    return ownedTiles;
}
std::string const City::getName() {
    return name;
}
Civilization* const City::getOwner() {
    return owner;
}
int const City::getX() {
    return x;
}
int const City::getY() {
    return y;
}
int const City::getFood() {
    return food;
}
int const City::getPopulation() {
    return population;
}
int const City::getHealth() {
    return health;
}
int const City::getMaxHealth() {
    return maxHealth;
}

void City::takeDamage(int damage) {
    this->health -= damage;
    if (this->health <= 0) {
        // TODO: Сделать механику разрушения города
    }
}

void City::repair(int health) {
    this->health += health;
    if (this->maxHealth <= this->health) {
        this->health = this->maxHealth;
    }
}

void City::update() {
    int newFood = 3;
    int newPopulation = 0;
    double bonus = 1;

    if (this->food < this->population) {
        bonus = 1/(food - population);
    }
    if (this->food-this->population >= this->population) {
        bonus = 1.5;
    }

    for (Tile* tile : ownedTiles) {
        Building* building = tile->getBuilding();
        if (building) {
            newFood += building->getFoodBonus();
            newPopulation += building->getPopulationBonus();
            this->owner->addGold(building->getGoldBonus() * bonus);
            this->owner->addScience(building->getScienceBonus() * bonus);
            if (building->getRequiredResource() <= Resource::Nothing && building->getType() == BuildingType::Production)
                this->owner->addResource(building->getRequiredResource(), building->getResourceBonus() * bonus);
        }
    }

    this->population = newPopulation;
    this->food = newFood;
}

void City::upgrade() {
    if (this->population >= this->populationForUpgrade) {
        this->populationForUpgrade += 5;
        this->maxHealth *= 4/3;
        this->health = this->maxHealth;
    // TODO: Добавить расширение теретории при повышении уровня
    }
}