#include <ctime>
#include <cstdlib>
#include <fmt/core.h>
#include <fmt/color.h>

#include "Game.h"
#include "Globals.h"
#include "Tile.h"


int main() {



    srand(time(nullptr));

    Game* game = new Game();
    game->showMainMenu();
    game->printMap();
}
