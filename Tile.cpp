//
// Created by Nikita on 28.05.2026.
//

#include "Tile.h"

// --------------CONSTRUCTOR---------------

Tile::Tile(TerrainType terrain, Resource resource, Building* building, Unit* unit) {
    this->terrain = terrain;
    this->resource = resource;
    this->building = building;
    this->unit = unit;
    this->revealed = false;
}

Tile::Tile(TerrainType terrain, Resource resource) {
    this->terrain = terrain;
    this->resource = resource;
    this->building = nullptr;
    this->unit = nullptr;
    this->owner = nullptr;
    this->revealed = false;
}

// --------------GETTER---------------

TerrainType const Tile::getTerrain() {
    return terrain;
}
Resource const Tile::getResource() {
    return resource;
}
Building* const Tile::getBuilding() {
    return building;
}
Unit* const Tile::getUnit() {
    return unit;
}
City* const Tile::getOwner() {
    return owner;
}
Citystate* const Tile::getCitystateOwner() {
    return citystateOwner;
}
bool const Tile::getRevealed() {
    return revealed;
}

// --------------SETTER---------------

void Tile::setTerrain(TerrainType terrain) {
    this->terrain = terrain;
}
void Tile::setResource(Resource resource) {
    this->resource = resource;
}
void Tile::setBuilding(Building* building) {
    this->building = building;
}
void Tile::setUnit(Unit* unit) {
    this->unit = unit;
}
void Tile::setOwner(City* city) {
    if (this->citystateOwner != nullptr) {
        this->citystateOwner = nullptr;
    }
    this->owner = city;
}
void Tile::setCitystateOwner(Citystate* citystate) {
    if (this->owner != nullptr) {
        this->owner = nullptr;
    }
    this->citystateOwner = citystate;
}
void Tile::setRevealed(bool revealed) {
    this->revealed = revealed;
}

// --------------GAME LOGIC--------------

int Tile::getMovementCost(UnitType unitType) {
    if (this->unit != nullptr) {
        return -1; // Returns -1 if tile has unit
    }
    if (this->building.getBuildingType() == BuildingType::City) {
        return -2; // Returns -2 if tile has city
    }
    if (this->citystateOwner != nullptr && this->citystateOwner->getIsInWar()) {
        return -3; // Returns -3 if tile owned by cityState without war
    }


    switch (this->terrain) {
        case TerrainType::Plains:
            switch (unitType) {
                case UnitType::Melee:
                    return 1;
                case UnitType::Ranged:
                    return 1;
                case UnitType::Cavalry:
                    return 1;
                case UnitType::AntiCavalry:
                    return 1;
                case UnitType::Siege:
                    return 1;
                case UnitType::Naval:
                    return -4;
            }
        case TerrainType::Mountains:
            switch (unitType) {
            case UnitType::Melee:
                    return -4;
            case UnitType::Ranged:
                    return -4;
            case UnitType::Cavalry:
                    return -4;
            case UnitType::AntiCavalry:
                    return -4;
            case UnitType::Siege:
                    return -4;
            case UnitType::Naval:
                    return -4;
            }
        case TerrainType::Rivers:
            switch (unitType) {
            case UnitType::Melee:
                    return 2;
            case UnitType::Ranged:
                    return 2;
            case UnitType::Cavalry:
                    return 3;
            case UnitType::AntiCavalry:
                    return 2;
            case UnitType::Siege:
                    return 3;
            case UnitType::Naval:
                    return -4;
            }
        case TerrainType::Forest:
            switch (unitType) {
            case UnitType::Melee:
                    return 2;
            case UnitType::Ranged:
                    return 2;
            case UnitType::Cavalry:
                    return 3;
            case UnitType::AntiCavalry:
                    return 2;
            case UnitType::Siege:
                    return 3;
            case UnitType::Naval:
                    return -4;
            }
        case TerrainType::Desert:
            switch (unitType) {
            case UnitType::Melee:
                    return 1;
            case UnitType::Ranged:
                    return 1;
            case UnitType::Cavalry:
                    return 1;
            case UnitType::AntiCavalry:
                    return 1;
            case UnitType::Siege:
                    return 2;
            case UnitType::Naval:
                    return -4;
            }
        case TerrainType::Shallow:
            switch (unitType) {
            case UnitType::Melee:
                    return -4;
            case UnitType::Ranged:
                    return -4;
            case UnitType::Cavalry:
                    return -4;
            case UnitType::AntiCavalry:
                    return -4;
            case UnitType::Siege:
                    return -4;
            case UnitType::Naval:
                    return 1;
            }
        case TerrainType::Ocean:
            switch (unitType) {
            case UnitType::Melee:
                    return -4;
            case UnitType::Ranged:
                    return -4;
            case UnitType::Cavalry:
                    return -4;
            case UnitType::AntiCavalry:
                    return -4;
            case UnitType::Siege:
                    return -4;
            case UnitType::Naval:
                    return 1;
            }
    }
}

// TODO: Сделать метод printTile()
void Tile::printTile(MapView *mapView) {

}
