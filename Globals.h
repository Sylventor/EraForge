//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_COLORS_H
#define UNTITLED_COLORS_H

// Colors

#define PLAINS_C fmt::rgb(134, 194, 62)
#define MOUNTAINS_C1 fmt::rgb(99, 95, 92)
#define MOUNTAINS_C2 fmt::rgb(255, 255, 255)
#define RIVER_C fmt::rgb(88, 140, 214)
#define FOREST_C1 fmt::rgb(34, 122, 12)
#define FOREST_C2 fmt::rgb(24, 87, 9)
#define DESERT_C fmt::rgb(222, 198, 111)
#define SHALLOW_C1 fmt::rgb(35, 111, 219)
#define SHALLOW_C2 fmt::rgb(113, 165, 240)
#define OCEAN_C1 fmt::rgb(18, 86, 184)
#define OCEAN_C2 fmt::rgb(82, 152, 255)

#define IRON_C fmt::rgb(105, 75, 66)
#define HORSES_C fmt::rgb(87, 46, 6)
#define ROCK_C fmt::rgb(143, 143, 143)
#define COAL_C fmt::rgb(31, 31, 31)

// Enums

enum class MapView {
    Terrain,
    Politic,
    Resources
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

#endif //UNTITLED_COLORS_H
