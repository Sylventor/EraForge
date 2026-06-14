//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_COLORS_H
#define UNTITLED_COLORS_H

#include <map>
#include <windows.h>

#include "fmt/color.h"

// Colors

#define PLAINS_C fmt::rgb(134, 194, 62)
#define MOUNTAINS_C1 fmt::rgb(99, 95, 92)
#define MOUNTAINS_C2 fmt::rgb(255, 255, 255)
#define RIVER_C fmt::rgb(88, 140, 214)
#define FOREST_C1 fmt::rgb(34, 122, 12)
#define FOREST_C2 fmt::rgb(24, 87, 9)
#define DESERT_C1 fmt::rgb(222, 198, 111)
#define DESERT_C2 fmt::rgb(194, 172, 91)
#define SHALLOW_C1 fmt::rgb(35, 111, 219)
#define SHALLOW_C2 fmt::rgb(113, 165, 240)
#define OCEAN_C1 fmt::rgb(18, 86, 184)
#define OCEAN_C2 fmt::rgb(82, 152, 255)

#define IRON_C fmt::rgb(105, 75, 66)
#define HORSES_C fmt::rgb(87, 46, 6)
#define ROCK_C fmt::rgb(143, 143, 143)
#define COAL_C fmt::rgb(31, 31, 31)
#define ROCKS_C fmt::rgb(99, 95, 92)

#define COLOR1 fmt::rgb(120, 133, 156)
#define COLOR2 fmt::rgb(255, 255, 255)
#define COLOR3 fmt::rgb(0, 0, 0)

#define NOT_REVEALED_C1 fmt::rgb(50, 50, 50)
#define NOT_REVEALED_C2 fmt::rgb(80, 80, 80)

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

// Maps

const std::map<TerrainType, std::string> terrain_icons = {
    {TerrainType::Plains, " "},
    {TerrainType::Mountains, "^"},
    {TerrainType::Rivers, "~"},
    {TerrainType::Forest, "♣"},
    {TerrainType::Desert, "ᴖ"},
    {TerrainType::Shallow, "~"},
    {TerrainType::Ocean, "~"}
};

const std::map<TerrainType, fmt::rgb> terrain_fg = {
    {TerrainType::Plains, COLOR3},
    {TerrainType::Mountains, MOUNTAINS_C2},
    {TerrainType::Rivers, RIVER_C},
    {TerrainType::Forest, FOREST_C2},
    {TerrainType::Desert, DESERT_C2},
    {TerrainType::Shallow, SHALLOW_C2},
    {TerrainType::Ocean, OCEAN_C2}
};

const std::map<TerrainType, fmt::rgb> terrain_bg = {
    {TerrainType::Plains, PLAINS_C},
    {TerrainType::Mountains, MOUNTAINS_C1},
    {TerrainType::Rivers, PLAINS_C},
    {TerrainType::Forest, FOREST_C1},
    {TerrainType::Desert, DESERT_C1},
    {TerrainType::Shallow, SHALLOW_C1},
    {TerrainType::Ocean, OCEAN_C1}
};

const std::map<UnitType, std::string> unit_icons = {
    {UnitType::Melee, "M"},
    {UnitType::Ranged, "R"},
    {UnitType::Cavalry, "C"},
    {UnitType::AntiCavalry, "A"},
    {UnitType::Siege, "S"},
    {UnitType::Naval, "N"}
};

const std::map<Resource, std::string> resource_icons = {
    {Resource::Nothing, " "},
    {Resource::Iron, "◉"},
    {Resource::Horses, "♞"},
    {Resource::Coal, "●"},
    {Resource::Rocks, "■"},
};

const std::map<Resource, fmt::rgb> resource_fg = {
    {Resource::Nothing, COLOR3},
    {Resource::Iron, IRON_C},
    {Resource::Horses, HORSES_C},
    {Resource::Coal, COAL_C},
    {Resource::Rocks, ROCKS_C}
};

// Constants

constexpr int MAP_SIZE_X = 50;
constexpr int MAP_SIZE_Y = 50;

#endif //UNTITLED_COLORS_H
