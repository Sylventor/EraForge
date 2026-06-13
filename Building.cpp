//
// Created by Nikita on 28.05.2026.
//

#include "Building.h"


Building::Building(std::string name, std::string icon, BuildingType type, int foodBonus, int goldBonus, int populationBonus,
                   int scienceBonus, int resourceBonus, int cost, Resource requiredResource,
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
    this->requiredResource = requiredResource;
    this->requiredTerrain = requiredTerrain;
}

std::string const Building::getName() {
    return name;
}
std::string const Building::getIcon() {
    return icon;
}
BuildingType const Building::getType() {
    return type;
}
int const Building::getFoodBonus() {
    return foodBonus;
}
int const Building::getGoldBonus() {
    return goldBonus;
}
int const Building::getPopulationBonus() {
    return populationBonus;
}
int const Building::getScienceBonus() {
    return scienceBonus;
}
int const Building::getResourceBonus() {
    return resourceBonus;
}
Resource const Building::getRequiredResource() {
    return requiredResource;
}
std::vector<TerrainType> const Building::getRequiredTerrain() {
    return requiredTerrain;
}
int const Building::getCost() {
    return cost;
}


void Building::upgrade() {
    // TODO: Доделать метод upgrade
}
