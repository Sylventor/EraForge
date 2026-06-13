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
    std::string icon;
    BuildingType type;
    int foodBonus;
    int goldBonus;
    int populationBonus;
    int scienceBonus;
    int resourceBonus;
    int cost;
    Resource requiredResource;
    std::vector<TerrainType> requiredTerrain;
public:
    Building(std::string name, std::string icon, BuildingType type, int foodBonus, int goldBonus, int populationBonus, int scienceBonus, int resourceBonus, int cost, Resource requiredResource, std::vector<TerrainType> requiredTerrain);

    std::string const getName();
    std::string const getIcon();
    BuildingType const getType();
    int const getFoodBonus();
    int const getGoldBonus();
    int const getPopulationBonus();
    int const getScienceBonus();
    int const getResourceBonus();
    int const getCost();
    Resource const getRequiredResource();
    std::vector<TerrainType> const getRequiredTerrain();

    void upgrade();
};


#endif //UNTITLED_BUILDING_H
