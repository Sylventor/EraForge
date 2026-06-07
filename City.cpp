//
// Created by Nikita on 28.05.2026.
//

#include "City.h"

#include "Building.h"
#include "Tile.h"
#include "Civilization.h"

City::City(Civilization* owner, int x, int y, std::string name) {}

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
    int newFood = 0;
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
        this->maxHealth *= 1.5;
        this->health = this->maxHealth;
    }
}