//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_COLORS_H
#define UNTITLED_COLORS_H

#include <map>
#include <vector>
#include <fmt/color.h>

#include "Building.h"
#include "Unit.h"
#include "Citystate.h"

// Colors

#define PLAINS_C1 fmt::rgb(134, 194, 62)
#define PLAINS_C2 fmt::rgb(95, 150, 29)
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
#define COLOR4 fmt::rgb(57, 69, 89)
#define COLOR5 fmt::rgb(98, 201, 14)

#define COLOR_GOLD fmt::rgb(242, 195, 24)
#define COLOR_SCIENCE fmt::rgb(96, 171, 224)

#define NOT_REVEALED_C1 fmt::rgb(50, 50, 50)
#define NOT_REVEALED_C2 fmt::rgb(80, 80, 80)

// Maps

const std::map<TerrainType, std::string> terrain_icons = {
    {TerrainType::Plains, "░"},
    {TerrainType::Mountains, "^"},
    {TerrainType::Rivers, "~"},
    {TerrainType::Forest, "♣"},
    {TerrainType::Desert, "ᴖ"},
    {TerrainType::Shallow, "~"},
    {TerrainType::Ocean, "~"}
};

const std::map<TerrainType, fmt::rgb> terrain_fg = {
    {TerrainType::Plains, PLAINS_C2},
    {TerrainType::Mountains, MOUNTAINS_C2},
    {TerrainType::Rivers, RIVER_C},
    {TerrainType::Forest, FOREST_C2},
    {TerrainType::Desert, DESERT_C2},
    {TerrainType::Shallow, SHALLOW_C2},
    {TerrainType::Ocean, OCEAN_C2}
};

const std::map<TerrainType, fmt::rgb> terrain_bg = {
    {TerrainType::Plains, PLAINS_C1},
    {TerrainType::Mountains, MOUNTAINS_C1},
    {TerrainType::Rivers, PLAINS_C1},
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

const std::map<Resource, std::string> resource_names = {
    {Resource::Nothing, " "},
    {Resource::Iron, "Iron"},
    {Resource::Horses, "Horses"},
    {Resource::Coal, "Coal"},
    {Resource::Rocks, "Rocks"},
};

const std::map<Resource, fmt::rgb> resource_fg = {
    {Resource::Nothing, COLOR3},
    {Resource::Iron, IRON_C},
    {Resource::Horses, HORSES_C},
    {Resource::Coal, COAL_C},
    {Resource::Rocks, ROCKS_C}
};

// Objects

static Building b_city{
    "City","C",BuildingType::City,
    3,2,5,1,1,
    500,0,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert, TerrainType::Rivers}
};
static Building b_farm{
    "Farm","F",BuildingType::Economy,
    4,0,1,0,0,
    60,20,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Rivers}
};
static Building b_granary{
    "Granary","G",BuildingType::Economy,
    8,0,3,0,0,
    120,50,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Rivers}
};
static Building b_aqueduct{
    "Aqueduct","A",BuildingType::Economy,
    12,0,5,0,0,
    250,120,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Rivers}
};
static Building b_lumber{
    "Lumber","L",BuildingType::Production,
    2,2,0,0,0,
    80,25,
    Resource::Nothing,
    {TerrainType::Forest}
};
static Building b_sawmill{
    "Sawmill","S",BuildingType::Production,
    3,4,0,0,0,
    180,80,
    Resource::Nothing,
    {TerrainType::Forest}
};
static Building b_mine{
    "Mine","M",BuildingType::Production,
    0,1,0,0,4,
    100,30,
    Resource::Iron,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert}
};
static Building b_quarry{
    "Quarry","Q",BuildingType::Production,
    0,1,0,0,5,
    120,40,
    Resource::Rocks,
    {TerrainType::Plains, TerrainType::Desert}
};
static Building b_forge{
    "Forge","F",BuildingType::Production,
    0,2,0,0,6,
    200,90,
    Resource::Iron,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert}
};
static Building b_workshop{
    "Workshop","W",BuildingType::Production,
    0,2,0,1,8,
    300,150,
    Resource::Rocks,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert}
};
static Building b_factory{
    "Factory","Y",BuildingType::Production,
    0,4,0,2,12,
    600,350,
    Resource::Coal,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert}
};
static Building b_factory_d{
    "Industrial","D",BuildingType::Production,
    0,6,0,4,18,
    1000,700,
    Resource::Coal,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert}
};
static Building b_market{
    "Market","$",BuildingType::Economy,
    0,4,0,0,0,
    120,50,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert, TerrainType::Rivers}
};
static Building b_trading{
    "Trading","T",BuildingType::Economy,
    0,7,0,0,0,
    250,120,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert, TerrainType::Rivers}
};
static Building b_bank{
    "Bank","B",BuildingType::Economy,
    0,12,0,0,0,
    500,300,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert, TerrainType::Rivers}
};
static Building b_stock{
    "Stock","S",BuildingType::Economy,
    0,20,0,0,0,
    900,700,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert, TerrainType::Rivers}
};
static Building b_port{
    "Port","P",BuildingType::Economy,
    3,5,0,1,0,
    250,120,
    Resource::Nothing,
    {TerrainType::Shallow}
};
static Building b_harbor{
    "Harbor","H",BuildingType::Economy,
    5,10,0,2,0,
    500,300,
    Resource::Nothing,
    {TerrainType::Shallow}
};
static Building b_library{
    "Library","L",BuildingType::Science,
    0,0,0,4,0,
    120,80,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert, TerrainType::Rivers}
};
static Building b_temple{
    "Temple","T",BuildingType::Science,
    1,0,1,3,0,
    100,60,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert, TerrainType::Rivers}
};
static Building b_university{
    "University","U",BuildingType::Science,
    0,0,2,10,0,
    350,250,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert, TerrainType::Rivers}
};
static Building b_observatory{
    "Observatory","O",BuildingType::Science,
    0,0,0,14,0,
    500,400,
    Resource::Nothing,
    {TerrainType::Mountains}
};
static Building b_lab{
    "Lab","R",BuildingType::Science,
    0,0,0,20,0,
    900,800,
    Resource::Coal,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert}
};
static Building b_academy{
    "Academy","A",BuildingType::Science,
    0,0,3,25,0,
    1400,1200,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert, TerrainType::Rivers}
};
static Building b_barracks{
    "Barracks","B",BuildingType::Military,
    0,0,0,0,0,
    150,80,
    Resource::Iron,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert}
};
static Building b_armory{
    "Armory","A",BuildingType::Military,
    0,1,0,0,2,
    250,150,
    Resource::Iron,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert}
};
static Building b_stable{
    "Stable","S",BuildingType::Military,
    2,1,0,0,2,
    180,90,
    Resource::Horses,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert}
};
static Building b_watchtower{
    "Watchtower","T",BuildingType::Military,
    0,1,0,0,0,
    100,40,
    Resource::Nothing,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert}
};
static Building b_castle{
    "Castle","C",BuildingType::Military,
    0,3,2,1,0,
    600,400,
    Resource::Rocks,
    {TerrainType::Plains, TerrainType::Forest, TerrainType::Desert}
};

static std::vector<Building> b_list{b_city, b_farm, b_granary, b_aqueduct, b_lumber, b_sawmill, b_mine, b_quarry, b_forge, b_workshop, b_factory, b_factory_d, b_market, b_trading, b_bank, b_stock, b_port, b_harbor, b_library, b_temple, b_university, b_observatory, b_lab, b_academy, b_barracks, b_armory, b_stable, b_watchtower, b_castle};

static Unit u_warrior{"Warrior",-1,-1,100,10,2,1,UnitType::Melee,50,10,{{Resource::Nothing,0}},nullptr};
static Unit u_spearman{"Spearman",-1,-1,110,12,2,1,UnitType::AntiCavalry,70,20,{{Resource::Iron,1}},nullptr};
static Unit u_archer{"Archer",-1,-1,80,15,2,2,UnitType::Ranged,80,25,{{Resource::Nothing,0}},nullptr};
static Unit u_horse{"Horseman",-1,-1,120,18,4,1,UnitType::Cavalry,140,60,{{Resource::Horses,1}},nullptr};
static Unit u_knight{"Knight",-1,-1,180,25,4,1,UnitType::Cavalry,240,120,{{Resource::Horses,2}},nullptr};
static Unit u_catapult{"Catapult",-1,-1,70,30,2,3,UnitType::Siege,180,90,{{Resource::Rocks,1}},&b_workshop};
static Unit u_trebuchet{"Trebuchet",-1,-1,80,40,2,4,UnitType::Siege,280,160,{{Resource::Rocks,2}},&b_factory};
static Unit u_swords{"Swordsman",-1,-1,140,20,2,1,UnitType::Melee,120,40,{{Resource::Iron,1}},&b_barracks};
static Unit u_pike{"Pikeman",-1,-1,130,18,2,1,UnitType::AntiCavalry,110,35,{{Resource::Iron,1}},&b_barracks};
static Unit u_cross{"Crossbow",-1,-1,90,22,2,2,UnitType::Ranged,130,50,{{Resource::Nothing,0}},&b_market};
static Unit u_longbow{"Longbow",-1,-1,100,26,2,3,UnitType::Ranged,170,70,{{Resource::Nothing,0}},&b_market};
static Unit u_cannon{"Cannon",-1,-1,120,45,2,3,UnitType::Siege,360,180,{{Resource::Coal,1}},&b_factory};
static Unit u_tank{"Tank",-1,-1,300,60,3,1,UnitType::Melee,600,350,{{Resource::Coal,2}},&b_factory_d};
static Unit u_infantry{"Infantry",-1,-1,200,30,3,1,UnitType::Melee,220,120,{{Resource::Iron,1}},&b_barracks};
static Unit u_marine{"Marine",-1,-1,160,28,3,1,UnitType::Naval,200,90,{{Resource::Nothing,0}},&b_port};
static Unit u_destroyer{"Destroyer",-1,-1,220,40,4,2,UnitType::Naval,420,220,{{Resource::Coal,1}},&b_harbor};
static Unit u_sub{"Submarine",-1,-1,180,35,4,1,UnitType::Naval,380,200,{{Resource::Coal,1}},&b_harbor};
static Unit u_scout{"Scout",-1,-1,60,5,5,1,UnitType::Melee,30,5,{{Resource::Nothing,0}},nullptr};
static Unit u_spy{"Spy",-1,-1,50,-1,5,1,UnitType::Melee,90,40,{{Resource::Nothing,0}},nullptr};
static Unit u_art{"Artillery",-1,-1,100,50,2,4,UnitType::Siege,450,250,{{Resource::Coal,2}},&b_factory_d};
static Unit u_heli{"Helicopter",-1,-1,180,40,5,2,UnitType::Cavalry,520,300,{{Resource::Coal,2}},&b_factory_d};

static std::vector<Unit> u_list = {u_warrior, u_spearman, u_archer, u_horse, u_knight, u_catapult, u_trebuchet, u_swords, u_pike, u_cross, u_longbow, u_cannon, u_tank, u_marine, u_destroyer, u_sub, u_scout, u_spy, u_art, u_heli};

static Citystate cs1{"Athena",CitystateType::Science,{(Unit*)&u_archer},200,10,500,25,-1,-1,300,500, fmt::rgb(176, 42, 42)};
static Citystate cs2{"Sparta",CitystateType::Military,{(Unit*)&u_swords},300,15,100,5,-1,-1,400,600, fmt::rgb(199, 199, 18)};
static Citystate cs3{"Venice",CitystateType::Economic,{(Unit*)&u_marine},400,25,200,10,-1,-1,350,550, fmt::rgb(42, 199, 18)};
static Citystate cs4{"Alexandria",CitystateType::Science,{(Unit*)&u_cross},250,12,450,20,-1,-1,320,500, fmt::rgb(16, 196, 193)};
static Citystate cs5{"Rome",CitystateType::Military,{(Unit*)&u_infantry},500,20,300,15,-1,-1,600,800, fmt::rgb(22, 113, 217)};
static Citystate cs6{"Carthage",CitystateType::Economic,{(Unit*)&u_horse},350,18,250,12,-1,-1,400,600, fmt::rgb(109, 7, 242)};
static Citystate cs7{"Babylon",CitystateType::Science,{(Unit*)&u_spearman},280,14,600,30,-1,-1,300,500, fmt::rgb(230, 9, 185)};
static Citystate cs8{"Tokyo",CitystateType::Military,{(Unit*)&u_knight},450,22,350,18,-1,-1,500,700, fmt::rgb(162, 212, 25)};

static std::vector<Citystate> cs_list = {cs1, cs2, cs3, cs4, cs5, cs6, cs7, cs8};

// City names

static const std::vector<std::string> CITY_NAMES = {
    "Athens",
    "Sparta",
    "Corinth",
    "Thebes",
    "Argos",
    "Delphi",
    "Olympia",
    "Rhodes",
    "Knossos",
    "Ephesus",

    "Rome",
    "Neapolis",
    "Mediolanum",
    "Ravenna",
    "Pompeii",
    "Capua",
    "Tarentum",
    "Brundisium",
    "Syracuse",
    "Aquileia",

    "Babylon",
    "Ur",
    "Uruk",
    "Nineveh",
    "Akkad",
    "Nippur",
    "Eridu",
    "Lagash",
    "Assur",
    "Mari",

    "Alexandria",
    "Memphis",
    "ThebesEgypt",
    "Heliopolis",
    "Giza",
    "Abydos",
    "Amarna",
    "Tanis",
    "Sais",
    "Elephantine",

    "Jerusalem",
    "Damascus",
    "Tyre",
    "Sidon",
    "Byblos",
    "Antioch",
    "Palmyra",
    "Gaza",
    "Jericho",
    "Aleppo",

    "Carthage",
    "Utica",
    "Hippo",
    "Leptis",
    "Thapsus",
    "Hadrumetum",
    "Cirta",
    "Volubilis",
    "Tingis",
    "Lixus",

    "Constantinople",
    "Byzantium",
    "Nicaea",
    "Trebizond",
    "Edirne",
    "Smyrna",
    "Ankara",
    "Pergamon",
    "Miletus",
    "Halicarnassus",

    "Paris",
    "London",
    "York",
    "Dublin",
    "Edinburgh",
    "Lisbon",
    "Madrid",
    "Barcelona",
    "Seville",
    "Valencia",

    "Prague",
    "Vienna",
    "Budapest",
    "Warsaw",
    "Krakow",
    "Brno",
    "Ostrava",
    "Bratislava",
    "Zagreb",
    "Ljubljana",

    "Kyiv",
    "Lviv",
    "Kharkiv",
    "Odessa",
    "Dnipro",
    "Chernihiv",
    "Poltava",
    "Vinnytsia",
    "Zhytomyr",
    "Lutsk"
};


#endif //UNTITLED_COLORS_H
