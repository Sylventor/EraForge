//
// Created by Nikita on 28.05.2026.
//

#include "Civilization.h"
#include "City.h"
#include "Unit.h"

Civilization::Civilization(int startGold, std::vector<Building*> startResearchedBuildings, std::vector<Unit*> startResearchedUnits) {
    this->gold = startGold;
    this->science = 1000;
    this->researchedBuildings = startResearchedBuildings;
    this->researchedUnits = startResearchedUnits;
}

int const Civilization::getGold() {
    return this->gold;
}
int const Civilization::getScience() {
    return this->science;
}
std::map<Resource, int> const Civilization::getResources() {
    return this->resources;
}
std::vector<City*> const Civilization::getCities() {
    return this->cities;
}
std::vector<Unit*> const Civilization::getUnits() {
    return this->units;
}
std::vector<Building*> const Civilization::getResearchedBuildings() {
    return this->researchedBuildings;
}
std::vector<Unit*> const Civilization::getResearchedUnits() {
    return this->researchedUnits;
}

bool Civilization::researchBuilding(Building* building, int cost) {
    if (this->science < cost) {
        return false;
    }
    this->researchedBuildings.push_back(building);
    this->science -= cost;
    return true;
}
bool Civilization::researchUnit(Unit* unit, int cost) {
    if (this->science < cost) {
        return false;
    }
    this->researchedUnits.push_back(unit);
    this->science -= cost;
    return true;
}
void Civilization::addGold(int amount) {
    this->gold += amount;
}
void Civilization::addScience(int amount) {
    this->science += amount;
}
void Civilization::addCity(City* city) {
    this->cities.push_back(city);
}
void Civilization::addResource(Resource resource, int amount)
{
    if (resource == Resource::Nothing)
        return;

    resources[resource] += amount;
}
void Civilization::addUnit(Unit* unit) {
    this->units.push_back(unit);
}

void Civilization::removeGold(int amount) {
    if (this->gold > amount) {
        this->gold -= amount;
    } else {
        this->gold = 0;
    }
}
void Civilization::removeScience(int amount) {
    if (this->science > amount) {
        this->science -= amount;
    } else {
        this->science = 0;
    }
}
void Civilization::removeResource(Resource resource, int amount)
{
    if (resource == Resource::Nothing)
        return;

    auto it = resources.find(resource);

    if (it == resources.end())
        return;

    it->second -= amount;

    if (it->second <= 0)
        resources.erase(it);
}
void Civilization::removeCity(int index) {
    delete cities[index];
    cities.erase(cities.begin() + index);
}
void Civilization::removeUnit(int index) {
    delete units[index];
    units.erase(units.begin() + index);
}

void Civilization::update() {} // TODO: Доделать функцию update в Civilization
