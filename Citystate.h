//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_CITYSTATE_H
#define UNTITLED_CITYSTATE_H
#include <string>
#include <vector>

#include "Globals.h"

class Unit{};

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
    bool isInWar;
public:
    void turn();
};


#endif //UNTITLED_CITYSTATE_H
