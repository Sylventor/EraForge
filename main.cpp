#include <fmt/core.h>
#include <fmt/color.h>

#include "Globals.h"
#include "Tile.h"


int main() {

    fmt::print(fg(COLOR1), R"(
 ██████████                     ███████████
░░███░░░░░█                    ░░███░░░░░░█
 ░███  █ ░  ████████   ██████   ░███   █ ░   ██████  ████████   ███████  ██████
 ░██████   ░░███░░███ ░░░░░███  ░███████    ███░░███░░███░░███ ███░░███ ███░░███
 ░███░░█    ░███ ░░░   ███████  ░███░░░█   ░███ ░███ ░███ ░░░ ░███ ░███░███████
 ░███ ░   █ ░███      ███░░███  ░███  ░    ░███ ░███ ░███     ░███ ░███░███░░░
 ██████████ █████    ░░████████ █████      ░░██████  █████    ░░███████░░██████
░░░░░░░░░░ ░░░░░      ░░░░░░░░ ░░░░░        ░░░░░░  ░░░░░      ░░░░░███ ░░░░░░
                                                               ███ ░███
                                                              ░░██████
                                                               ░░░░░░

)");

    /*
    fmt::print("Plains with iron: ");
    fmt::print(bg(PLAINS_C) | fg(IRON_C)," ◉ \n");
    fmt::print("Mountain: ");
    fmt::print(bg(MOUNTAINS_C1) | fg(MOUNTAINS_C2),"^^^\n");
    fmt::print("Ocean: ");
    fmt::print(bg(OCEAN_C1) | fg(OCEAN_C2),"~~~\n");
    fmt::print("Shallow: ");
    fmt::print(bg(SHALLOW_C1) | fg(SHALLOW_C2),"~~~\n");
    fmt::print("Ocean and shallow: ");
    fmt::print(bg(SHALLOW_C1) | fg(SHALLOW_C2),"~~~");
    fmt::print(bg(OCEAN_C1) | fg(OCEAN_C2),"~~~\n");*/

    Tile* tile1 = new Tile(TerrainType::Plains, Resource::Nothing);
    Tile* tile2 = new Tile(TerrainType::Mountains, Resource::Nothing);
    Tile* tile3 = new Tile(TerrainType::Rivers, Resource::Nothing);
    Tile* tile4 = new Tile(TerrainType::Forest, Resource::Nothing);
    Tile* tile5 = new Tile(TerrainType::Desert, Resource::Nothing);
    Tile* tile6 = new Tile(TerrainType::Shallow, Resource::Nothing);
    Tile* tile7 = new Tile(TerrainType::Ocean, Resource::Nothing);

    MapView mapView = MapView::Base;

    tile1->printTile(mapView);
    tile2->printTile(mapView);
    tile3->printTile(mapView);
    tile4->printTile(mapView);
    tile5->printTile(mapView);
    tile6->printTile(mapView);
    tile7->printTile(mapView);
}
