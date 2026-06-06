//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_BUILDING_H
#define UNTITLED_BUILDING_H
#include <string>
#include <vector>

#include "Globals.h"


class Building {
private:
    std::string name;
    char icon;
    BuildingType type;
    int foodBonus;
    int goldBonus;
    int populationBonus;
    int scienceBonus;
    int resourceBonus;
    Resource requiredResource;
    std::vector<TerrainType> requiredTerrain;
public:
    Building(std::string name, char icon, BuildingType type, int foodBonus, int goldBonus, int populationBonus, int scienceBonus, int resourceBonus, Resource requiredResource, std::vector<TerrainType> requiredTerrain);
    void upgrade();
};


#endif //UNTITLED_BUILDING_H
