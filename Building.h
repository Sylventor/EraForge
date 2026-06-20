//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_BUILDING_H
#define UNTITLED_BUILDING_H
#include <string>
#include <vector>

#include "Types.h"

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
    int researchCost;
    Resource requiredResource;
    std::vector<TerrainType> requiredTerrain;
public:
    Building(std::string name, std::string icon, BuildingType type, int foodBonus, int goldBonus, int populationBonus, int scienceBonus, int resourceBonus, int cost, int researchCost, Resource requiredResource, std::vector<TerrainType> requiredTerrain);
    Building(const Building& building);

    std::string getName() const;
    std::string getIcon() const;
    BuildingType getType() const;
    int getFoodBonus() const;
    int getGoldBonus() const;
    int getPopulationBonus() const;
    int getScienceBonus() const;
    int getResourceBonus() const;
    int getCost() const;
    int getResearchCost() const;
    Resource getRequiredResource() const;
    std::vector<TerrainType> getRequiredTerrain() const;

    void upgrade();
};


#endif //UNTITLED_BUILDING_H
