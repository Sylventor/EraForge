//
// Created by Nikita on 28.05.2026.
//

#include "Game.h"

Tile* const Game::getTile(int x, int y) {
    return this->map[x][y];
}