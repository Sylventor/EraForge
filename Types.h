//
// Created by Nikita on 14.06.2026.
//

#ifndef ERAFORGE_TYPES_H
#define ERAFORGE_TYPES_H

// Enums

enum class MapView {
    Terrain,
    Politic,
    Units,
    Base
};

enum class Resource {
    Nothing,
    Iron,
    Horses,
    Rocks,
    Coal
};

enum class TerrainType {
    Plains,
    Mountains,
    Rivers,
    Forest,
    Desert,
    Shallow,
    Ocean
};

enum class UnitType {
    Melee,
    Ranged,
    Cavalry,
    AntiCavalry,
    Siege,
    Naval
};

enum class BuildingType {
    City,
    Science,
    Economy,
    Production,
    Military
};

enum class CitystateType {
    Science,
    Economic,
    Military
};

// Constants

constexpr int MAP_SIZE_X = 50;
constexpr int MAP_SIZE_Y = 50;

#endif //ERAFORGE_TYPES_H
