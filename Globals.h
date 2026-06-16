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
#define COLOR4 fmt::rgb(57, 69, 89)

#define COLOR_GOLD fmt::rgb(242, 195, 24)
#define COLOR_SCIENCE fmt::rgb(96, 171, 224)

#define NOT_REVEALED_C1 fmt::rgb(50, 50, 50)
#define NOT_REVEALED_C2 fmt::rgb(80, 80, 80)

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

static Building b_city{"City","C",BuildingType::City,2,2,5,2,2,0,Resource::Nothing, std::vector<TerrainType>{TerrainType::Plains}};
static Building b_farm{"Farm","F",BuildingType::Economy,4,0,1,0,0,50,Resource::Nothing,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_mine{"Mine","M",BuildingType::Production,0,2,0,1,2,60,Resource::Iron,std::vector<TerrainType>{TerrainType::Mountains}};
static Building b_lumber{"Lumber","L",BuildingType::Production,1,1,0,0,2,40,Resource::Nothing,std::vector<TerrainType>{TerrainType::Forest}};
static Building b_market{"Market","$",BuildingType::Economy,0,5,0,0,0,80,Resource::Nothing,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_library{"Library","*",BuildingType::Science,0,0,0,5,0,90,Resource::Nothing,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_university{"University","U",BuildingType::Science,0,0,1,10,0,150,Resource::Nothing,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_barracks{"Barracks","B",BuildingType::Military,0,0,0,0,0,70,Resource::Iron,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_stable{"Stable","S",BuildingType::Military,1,1,0,0,1,80,Resource::Horses,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_port{"Port","P",BuildingType::Economy,2,4,0,1,0,120,Resource::Nothing,std::vector<TerrainType>{TerrainType::Shallow}};
static Building b_harbor{"Harbor","H",BuildingType::Economy,3,5,0,2,0,140,Resource::Nothing,std::vector<TerrainType>{TerrainType::Shallow}};
static Building b_workshop{"Workshop","W",BuildingType::Production,0,3,0,0,3,100,Resource::Rocks,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_factory{"Factory","F",BuildingType::Production,0,6,0,0,5,200,Resource::Coal,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_temple{"Temple","T",BuildingType::Science,1,0,1,3,0,90,Resource::Nothing,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_granary{"Granary","G",BuildingType::Economy,5,0,2,0,0,60,Resource::Nothing,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_aqueduct{"Aqueduct","A",BuildingType::Economy,6,0,3,0,0,130,Resource::Nothing,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_castle{"Castle","C",BuildingType::Military,0,2,2,1,0,180,Resource::Rocks,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_watchtower{"Watchtower","T",BuildingType::Military,0,1,0,0,0,60,Resource::Nothing,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_windmill{"Windmill","W",BuildingType::Production,2,2,0,0,1,80,Resource::Nothing,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_hydro{"Hydro","H",BuildingType::Production,0,4,0,3,3,220,Resource::Nothing,std::vector<TerrainType>{TerrainType::Rivers}};
static Building b_trading{"Trading","T",BuildingType::Economy,0,4,0,0,0,70,Resource::Nothing,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_bank{"Bank","B",BuildingType::Economy,0,8,0,0,0,160,Resource::Nothing,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_stock{"Stock","S",BuildingType::Economy,0,12,0,0,0,250,Resource::Nothing,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_lab{"Lab","R",BuildingType::Science,0,0,0,15,0,300,Resource::Coal,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_observatory{"Obs","O",BuildingType::Science,0,0,0,12,0,220,Resource::Nothing,std::vector<TerrainType>{TerrainType::Mountains}};
static Building b_forge{"Forge","F",BuildingType::Production,0,3,0,0,2,110,Resource::Iron,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_armory{"Armory","A",BuildingType::Military,0,2,0,0,1,100,Resource::Iron,std::vector<TerrainType>{TerrainType::Plains}};
static Building b_factory_d{"FactoryD","D",BuildingType::Production,0,10,0,0,6,400,Resource::Coal,std::vector<TerrainType>{TerrainType::Plains}};

static Unit u_warrior{"Warrior",-1,-1,100,10,2,1,UnitType::Melee,50,{{Resource::Nothing,0}},nullptr};
static Unit u_spearman{"Spearman",-1,-1,110,12,2,1,UnitType::AntiCavalry,60,{{Resource::Iron,1}},nullptr};
static Unit u_archer{"Archer",-1,-1,80,15,2,2,UnitType::Ranged,70,{{Resource::Nothing,0}},nullptr};
static Unit u_horse{"Horseman",-1,-1,120,18,4,1,UnitType::Cavalry,120,{{Resource::Horses,1}},nullptr};
static Unit u_knight{"Knight",-1,-1,180,25,4,1,UnitType::Cavalry,200,{{Resource::Horses,2}},nullptr};
static Unit u_catapult{"Catapult",-1,-1,70,30,2,3,UnitType::Siege,150,{{Resource::Rocks,1}},&b_workshop};
static Unit u_trebuchet{"Trebuchet",-1,-1,80,40,2,4,UnitType::Siege,220,{{Resource::Rocks,2}},&b_factory};
static Unit u_swords{"Swordsman",-1,-1,140,20,2,1,UnitType::Melee,100,{{Resource::Iron,1}},&b_barracks};
static Unit u_pike{"Pikeman",-1,-1,130,18,2,1,UnitType::AntiCavalry,90,{{Resource::Iron,1}},&b_barracks};
static Unit u_cross{"Crossbow",-1,-1,90,22,2,2,UnitType::Ranged,110,{{Resource::Nothing,0}},&b_market};
static Unit u_longbow{"Longbow",-1,-1,100,26,2,3,UnitType::Ranged,140,{{Resource::Nothing,0}},&b_market};
static Unit u_cannon{"Cannon",-1,-1,120,45,2,3,UnitType::Siege,300,{{Resource::Coal,1}},&b_factory};
static Unit u_tank{"Tank",-1,-1,300,60,3,1,UnitType::Melee,500,{{Resource::Coal,2}},&b_factory_d};
static Unit u_infantry{"Infantry",-1,-1,200,30,3,1,UnitType::Melee,200,{{Resource::Iron,1}},&b_barracks};
static Unit u_marine{"Marine",-1,-1,160,28,3,1,UnitType::Naval,180,{{Resource::Nothing,0}},&b_port};
static Unit u_destroyer{"Destroyer",-1,-1,220,40,4,2,UnitType::Naval,350,{{Resource::Coal,1}},&b_harbor};
static Unit u_sub{"Submarine",-1,-1,180,35,4,1,UnitType::Naval,300,{{Resource::Coal,1}},&b_harbor};
static Unit u_scout{"Scout",-1,-1,60,5,5,1,UnitType::Melee,30,{{Resource::Nothing,0}},nullptr};
static Unit u_spy{"Spy",-1,-1,50,-1,5,1,UnitType::Melee,80,{{Resource::Nothing,0}},nullptr};
static Unit u_art{"Artillery",-1,-1,100,50,2,4,UnitType::Siege,400,{{Resource::Coal,2}},&b_factory_d};
static Unit u_heli{"Helicopter",-1,-1,180,40,5,2,UnitType::Cavalry,450,{{Resource::Coal,2}},&b_factory_d};

static Citystate cs1{"Athena",CitystateType::Science,{(Unit*)&u_archer},200,10,500,25,-1,-1,300,500};
static Citystate cs2{"Sparta",CitystateType::Military,{(Unit*)&u_swords},300,15,100,5,-1,-1,400,600};
static Citystate cs3{"Venice",CitystateType::Economic,{(Unit*)&u_marine},400,25,200,10,-1,-1,350,550};
static Citystate cs4{"Alexandria",CitystateType::Science,{(Unit*)&u_cross},250,12,450,20,-1,-1,320,500};
static Citystate cs5{"Rome",CitystateType::Military,{(Unit*)&u_infantry},500,20,300,15,-1,-1,600,800};
static Citystate cs6{"Carthage",CitystateType::Economic,{(Unit*)&u_horse},350,18,250,12,-1,-1,400,600};
static Citystate cs7{"Babylon",CitystateType::Science,{(Unit*)&u_spearman},280,14,600,30,-1,-1,300,500};
static Citystate cs8{"Tokyo",CitystateType::Military,{(Unit*)&u_knight},450,22,350,18,-1,-1,500,700};

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
