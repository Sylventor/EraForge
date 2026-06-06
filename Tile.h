//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_TILE_H
#define UNTITLED_TILE_H
#include "Globals.h"

class Building;
class Unit;
class City;
class Citystate;

class Tile {
private:
    TerrainType terrain;
    Resource resource;
    Building* building;
    Unit* unit;
    City* owner;
    Citystate* citystateOwner;
    bool revealed = false;
public:
    Tile(TerrainType terrain, Resource resource, Building* building, Unit* unit);
    Tile(TerrainType terrain, Resource resource);

    TerrainType const getTerrain();
    Resource const getResource();
    Building* const getBuilding();
    Unit* const getUnit();
    City* const getOwner();
    Citystate* const getCitystateOwner();
    bool const getRevealed();

    void setTerrain(TerrainType terrain);
    void setResource(Resource resource);
    void setBuilding(Building* building);
    void setUnit(Unit* unit);
    void setOwner(City* owner);
    void setCitystateOwner(Citystate* citystate);
    void setRevealed(bool revealed);

    int getMovementCost(UnitType unitType);
    void printTile(MapView* mapView);
};


#endif //UNTITLED_TILE_H
