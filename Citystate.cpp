//
// Created by Nikita on 28.05.2026.
//

#include "Citystate.h"

Citystate::Citystate(std::string name, CitystateType type, std::vector<Unit*> units, int gold, int goldGain, int science, int scienceGain, int x, int y, int health, int maxHealth) {
    this->name = name;
    this->type = type;
    this->units = units;
    this->gold = gold;
    this->goldGain = goldGain;
    this->science = science;
    this->scienceGain = scienceGain;
    this->x = x;
    this->y = y;
    this->health = health;
    this->maxHealth = maxHealth;
    this->isInWar = false;
}

std::string const Citystate::getName() {
    return name;
}
CitystateType const Citystate::getType() {
    return type;
}
std::vector<Unit*> const Citystate::getUnits() {
    return units;
}
int const Citystate::getGold() {
    return gold;
}
int const Citystate::getScience() {
    return science;
}
int const Citystate::getGoldGain() {
    return goldGain;
}
int const Citystate::getScienceGain() {
    return scienceGain;
}
int const Citystate::getX() {
    return x;
}
int const Citystate::getY() {
    return y;
}
int const Citystate::getHealth() {
    return health;
}
int const Citystate::getMaxHealth() {
    return maxHealth;
}
bool const Citystate::getIsInWar() {
    return isInWar;
}

fmt::rgb const Citystate::getColor() {
    return color;
}

void Citystate::declareWar() {
    this->isInWar = true;
}

void Citystate::takeDamage(int damage) {
    this->health -= damage;
    if (this->health <= 0) {
        this->capture();
    }
}

// TODO: Сделать метод capture
void Citystate::capture() {

}
