//
// Created by Nikita on 28.05.2026.
//

#include "Building.h"


Building::Building(std::string name, std::string icon, BuildingType type, int foodBonus, int goldBonus, int populationBonus,
                   int scienceBonus, int resourceBonus, int cost, int researchCost, Resource requiredResource,
                   std::vector<TerrainType> requiredTerrain) {
    this->name = name;
    this->icon = icon;
    this->type = type;
    this->foodBonus = foodBonus;
    this->goldBonus = goldBonus;
    this->scienceBonus = scienceBonus;
    this->populationBonus = populationBonus;
    this->resourceBonus = resourceBonus;
    this->cost = cost;
    this->researchCost = researchCost;
    this->requiredResource = requiredResource;
    this->requiredTerrain = requiredTerrain;
}

Building::Building(const Building &building) : name(building.name), icon(building.icon), type(building.type),
                                               foodBonus(building.foodBonus), goldBonus(building.goldBonus),
                                               populationBonus(building.populationBonus),
                                               scienceBonus(building.scienceBonus),
                                               resourceBonus(building.resourceBonus),
                                               requiredTerrain(building.requiredTerrain),
                                               requiredResource(building.requiredResource), cost(building.cost),
                                               researchCost(building.researchCost) {
}

Building::Building(const Building* building) : name(building->name), icon(building->icon), type(building->type),
                                               foodBonus(building->foodBonus), goldBonus(building->goldBonus),
                                               populationBonus(building->populationBonus),
                                               scienceBonus(building->scienceBonus),
                                               resourceBonus(building->resourceBonus),
                                               requiredTerrain(building->requiredTerrain),
                                               requiredResource(building->requiredResource), cost(building->cost),
                                               researchCost(building->researchCost) {
}


std::string Building::getName() const {
    return name;
}
std::string Building::getIcon() const {
    return icon;
}
BuildingType Building::getType() const {
    return type;
}
int Building::getFoodBonus() const {
    return foodBonus;
}
int Building::getGoldBonus() const {
    return goldBonus;
}
int Building::getPopulationBonus() const {
    return populationBonus;
}
int Building::getScienceBonus() const {
    return scienceBonus;
}
int Building::getResourceBonus() const {
    return resourceBonus;
}
Resource Building::getRequiredResource() const {
    return requiredResource;
}
std::vector<TerrainType> Building::getRequiredTerrain() const {
    return requiredTerrain;
}
int Building::getCost() const {
    return cost;
}
int Building::getResearchCost() const {
    return researchCost;
}


void Building::upgrade() {
    // TODO: Доделать метод upgrade
}
