//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_TILE_H
#define UNTITLED_TILE_H
#include "Globals.h"

class Building{};
class Unit{};
class City{};

class Tile {
private:
    TerrainType terrain;
    Resource resource;
    Building* building;
    Unit* unit;
    City* owner;
    bool Revealed = false;
public:
    TerrainType getTerrain();
    Resource getResource();
    Building* getBuilding();
    Unit* getUnit();
    City* getOwner();
    bool getRevealed();

    void setTerrain(TerrainType terrain);
    void setResource(Resource resource);
    void setBuilding(Building* building);
    void setUnit(Unit* unit);
    void setOwner(City* owner);
    void setRevealed(bool revealed);

    
};


#endif //UNTITLED_TILE_H
