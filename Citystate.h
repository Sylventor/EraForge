//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_CITYSTATE_H
#define UNTITLED_CITYSTATE_H
#include <string>
#include <vector>

#include "Globals.h"
#include "fmt/color.h"

class Unit;

class Citystate {
private:
    std::string name;
    CitystateType type;
    std::vector<Unit*> units;
    int gold;
    int goldGain;
    int science;
    int scienceGain;
    int x;
    int y;
    int health;
    int maxHealth;
    bool isInWar;
    fmt::rgb color;
public:
    Citystate(std::string name, CitystateType type, std::vector<Unit*> units, int gold, int goldGain, int science, int scienceGain, int x, int y, int health, int maxHealth, bool isInWar);

    std::string const getName();
    CitystateType const getType();
    std::vector<Unit*> const getUnits();
    int const getGold();
    int const getScience();
    int const getGoldGain();
    int const getScienceGain();
    int const getX();
    int const getY();
    int const getHealth();
    int const getMaxHealth();
    bool const getIsInWar();
    fmt::rgb const getColor();

    void declareWar();
    void takeDamage(int damage);
    void capture();

    void turn();
};


#endif //UNTITLED_CITYSTATE_H
