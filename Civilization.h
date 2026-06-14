//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_CIVILIZATION_H
#define UNTITLED_CIVILIZATION_H
#include <map>
#include <vector>

#include "Globals.h"

class City;
class Unit;
class Building;

class Civilization {
private:
    int gold;
    int science;
    std::map<Resource, int> resources;
    std::vector<City*> cities;
    std::vector<Unit*> units;
    std::vector<Building*> researchedBuildings;
    std::vector<Unit*> researchedUnits;
public:
    Civilization(int startGold, int startScience, City* startCity);

    int const getGold();
    int const getScience();
    std::map<Resource, int> const getResources();
    std::vector<City*> const getCities();
    std::vector<Unit*> const getUnits();
    std::vector<Building*> const getResearchedBuildings();
    std::vector<Unit*> const getResearchedUnits();

    bool researchBuilding(Building* building, int cost);
    bool researchUnit(Unit* unit, int cost);

    void addGold(int amount);
    void addScience(int amount);
    void addResource(Resource resource, int amount);
    void addCity(City* city);
    void addUnit(Unit* unit);

    void removeGold(int amount);
    void removeScience(int amount);
    void removeResource(Resource resource, int amount);
    void removeCity(int index);
    void removeUnit(int index);

    void update();
};


#endif //UNTITLED_CIVILIZATION_H
