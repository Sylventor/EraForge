//
// Created by Nikita on 28.05.2026.
//

#include "Citystate.h"

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
