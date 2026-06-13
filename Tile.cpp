//
// Created by Nikita on 28.05.2026.
//

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/color.h>

#include "Tile.h"
#include "Building.h"
#include "Citystate.h"
#include "Unit.h"

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
    if (this->building->getType() == BuildingType::City) {
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
    return -5; // Returns -5 if other returns didn't work
}

void Tile::printTile(MapView mapView) {
    fmt::rgb bg_color;
    fmt::rgb fg_color1;
    fmt::rgb fg_color2;
    std::string terrain_icon;
    std::string icon;

    if (mapView == MapView::Terrain) {
        bg_color = terrain_bg.at(this->terrain);
        fg_color1 = terrain_fg.at(this->terrain);
        fg_color2 = resource_fg.at(this->resource);
        terrain_icon = terrain_icons.at(this->terrain);
        icon = resource_icons.at(this->resource);
    }
    else if (mapView == MapView::Units) {
        bg_color = terrain_bg.at(this->terrain);
        fg_color1 = terrain_fg.at(this->terrain);
        fg_color2 = COLOR2;
        terrain_icon = terrain_icons.at(this->terrain);
        if (unit) {
            icon = unit_icons.at(this->unit->getType());
        } else if (building) {
            icon = building->getIcon();
        } else {
            icon = U' ';
        }
    }
    else if (mapView == MapView::Politic) {
        if (citystateOwner) {
            bg_color = citystateOwner->getColor();
        } else if (owner) {
            bg_color = COLOR1;
        } else {
            bg_color = terrain_bg.at(this->terrain);
        }
        fg_color1 = COLOR2;
        fg_color2 = COLOR2;
        terrain_icon = U' ';

        if (unit) {
            icon = unit_icons.at(this->unit->getType());
        } else if (building) {
            icon = building->getIcon();
        } else {
            icon = U' ';
        }
    }
    else if (mapView == MapView::Base) {
        bg_color = terrain_bg.at(this->terrain);
        fg_color1 = terrain_fg.at(this->terrain);
        terrain_icon = terrain_icons.at(this->terrain);
        if (unit) {
            icon = unit_icons.at(this->unit->getType());
            fg_color2 = COLOR2;
        } else if (building) {
            icon = building->getIcon();
            fg_color2 = COLOR2;
        } else if (resource != Resource::Nothing) {
            icon = resource_icons.at(this->resource);
            fg_color2 = resource_fg.at(this->resource);
        } else {
            icon = terrain_icon;
            fg_color2 = fg_color1;
        }
    }

    fmt::print(bg(bg_color) | fg(fg_color1), "{}", terrain_icon);
    fmt::print(bg(bg_color) | fg(fg_color2), "{}", icon);
    fmt::print(bg(bg_color) | fg(fg_color1), "{}", terrain_icon);
}
