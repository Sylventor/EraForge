//
// Created by Nikita on 28.05.2026.
//

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>

#include "Game.h"

#include "Civilization.h"
#include "Tile.h"

static void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else
    std::system("clear");
#endif
}

static bool inBounds(int x, int y) {
    return x >= 0 && x < MAP_SIZE_X && y >= 0 && y < MAP_SIZE_Y;
}

static bool isWater(Tile* t) {
    return t->getTerrain() == TerrainType::Ocean ||
           t->getTerrain() == TerrainType::Shallow;
}

Game::Game() {
    this->selectedTileX = 0;
    this->selectedTileY = 0;
    this->player = nullptr;
    this->mapView = MapView::Base;
    this->generateMap();
}

Civilization* const Game::getPlayer() {
    return this->player;
}
Tile* const Game::getTile(int x, int y) {
    return this->map[x][y];
}
MapView const Game::getMapView() {
    return this->mapView;
}
int const Game::getSelectedTileX() {
    return this->selectedTileX;
}
int const Game::getSelectedTileY() {
    return this->selectedTileY;
}
Tile* const Game::getSelectedTile() {
    return this->getTile(this->selectedTileX, this->selectedTileY);
}

void Game::printMap() {
    for (int x = 0; x < MAP_SIZE_Y; x++) {
        for (int y = 0; y < MAP_SIZE_X; y++) {
            this->map[x][y]->printTile(this->mapView);
        }
        fmt::print("\n");
    }
}

void Game::generateMap()
{
    srand(time(nullptr));

    // 1. ВСЁ ОКЕАН
    for (int y = 0; y < MAP_SIZE_Y; y++) {
        for (int x = 0; x < MAP_SIZE_X; x++) {
            map[y][x] = new Tile(TerrainType::Ocean, Resource::Nothing);
        }
    }

    // 2. КОНТИНЕНТЫ (ростом)
    for (int c = 0; c < 10; c++)
    {
        int sx = rand() % MAP_SIZE_X;
        int sy = rand() % MAP_SIZE_Y;

        std::queue<std::pair<int,int>> q;
        q.push({sx, sy});

        int landTiles = 0;
        int target = 40 + rand() % 80;

        while (!q.empty() && landTiles < target)
        {
            auto [x, y] = q.front();
            q.pop();

            if (!inBounds(x, y)) continue;

            if (map[y][x]->getTerrain() != TerrainType::Ocean)
                continue;

            delete map[y][x];
            map[y][x] = new Tile(TerrainType::Plains, Resource::Nothing);
            landTiles++;

            const int dx[4] = {1, -1, 0, 0};
            const int dy[4] = {0, 0, 1, -1};

            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (!inBounds(nx, ny)) continue;

                if (rand() % 100 < 65) // форма континента
                    q.push({nx, ny});
            }
        }
    }

    // 3. SHALLOW (радиус 2 от суши)
    for (int y = 0; y < MAP_SIZE_Y; y++)
    {
        for (int x = 0; x < MAP_SIZE_X; x++)
        {
            if (map[y][x]->getTerrain() != TerrainType::Ocean)
                continue;

            bool nearLand = false;

            for (int dy = -2; dy <= 2 && !nearLand; dy++)
            {
                for (int dx = -2; dx <= 2; dx++)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx < 0 || ny < 0 || nx >= MAP_SIZE_X || ny >= MAP_SIZE_Y)
                        continue;

                    auto t = map[ny][nx]->getTerrain();

                    if (t != TerrainType::Ocean && t != TerrainType::Shallow)
                    {
                        nearLand = true;
                        break;
                    }
                }
            }

            if (nearLand)
            {
                delete map[y][x];
                map[y][x] = new Tile(TerrainType::Shallow, Resource::Nothing);
            }
        }
    }

    // 4. ГОРЫ (не рядом с водой)
    for (int i = 0; i < 360; i++)
    {
        int x = rand() % MAP_SIZE_X;
        int y = rand() % MAP_SIZE_Y;

        if (map[y][x]->getTerrain() != TerrainType::Plains)
            continue;

        bool nearWater = false;

        for (int dy = -1; dy <= 1; dy++)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                int nx = x + dx;
                int ny = y + dy;

                if (!inBounds(nx, ny)) continue;

                if (isWater(map[ny][nx]))
                    nearWater = true;
            }
        }

        if (nearWater) continue;

        map[y][x]->~Tile();
        map[y][x] = new Tile(TerrainType::Mountains, Resource::Nothing);
    }

    // 5. РЕКИ (из гор к воде)
    for (int i = 0; i < 2000; i++)
    {
        int x = rand() % MAP_SIZE_X;
        int y = rand() % MAP_SIZE_Y;

        if (map[y][x]->getTerrain() != TerrainType::Mountains)
            continue;

        for (int step = 0; step < 60; step++)
        {
            map[y][x]->~Tile();
            map[y][x] = new Tile(TerrainType::Rivers, Resource::Nothing);

            if (isWater(this->getTile(x, y)))
                break;

            int bestX = x;
            int bestY = y;
            int bestDist = 999999;

            for (int dy = -1; dy <= 1; dy++)
                for (int dx = -1; dx <= 1; dx++)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (!inBounds(nx, ny)) continue;
                    if (isWater(this->getTile(nx, ny))) goto end_river;

                    int dist = abs(nx - MAP_SIZE_X/2) + abs(ny - MAP_SIZE_Y/2);

                    if (dist < bestDist)
                    {
                        bestDist = dist;
                        bestX = nx;
                        bestY = ny;
                    }
                }

            x = bestX;
            y = bestY;
        }

        end_river:;
    }

    // 6. ЛЕСА
    for (int i = 0; i < 200; i++)
    {
        int x = rand() % MAP_SIZE_X;
        int y = rand() % MAP_SIZE_Y;

        if (map[y][x]->getTerrain() != TerrainType::Plains)
            continue;

        for (int dy = -2; dy <= 2; dy++)
            for (int dx = -2; dx <= 2; dx++)
            {
                int nx = x + dx;
                int ny = y + dy;

                if (!inBounds(nx, ny)) continue;

                if (rand() % 100 < 60 &&
                    map[ny][nx]->getTerrain() == TerrainType::Plains)
                {
                    map[ny][nx]->~Tile();
                    map[ny][nx] = new Tile(TerrainType::Forest, Resource::Nothing);
                }
            }
    }

    // 7. ПУСТЫНИ
    for (int i = 0; i < 120; i++)
    {
        int x = rand() % MAP_SIZE_X;
        int y = rand() % MAP_SIZE_Y;

        if (map[y][x]->getTerrain() != TerrainType::Plains)
            continue;

        for (int dy = -3; dy <= 3; dy++)
            for (int dx = -3; dx <= 3; dx++)
            {
                int nx = x + dx;
                int ny = y + dy;

                if (nx < 0 || ny < 0 || nx >= MAP_SIZE_X || ny >= MAP_SIZE_Y)
                    continue;

                if (map[ny][nx]->getTerrain() == TerrainType::Plains && (rand() % 100 < 40))
                {
                    map[ny][nx]->~Tile();
                    map[ny][nx] = new Tile(TerrainType::Desert, Resource::Nothing);
                }
            }
    }

    // 8. РЕСУРСЫ
    for (int y = 0; y < MAP_SIZE_Y; y++)
    {
        for (int x = 0; x < MAP_SIZE_X; x++)
        {
            Resource r = Resource::Nothing;
            TerrainType t = map[y][x]->getTerrain();

            if (t == TerrainType::Plains ||
                t == TerrainType::Forest ||
                t == TerrainType::Desert)
            {
                int roll = rand() % 75;

                if (roll < 4) r = Resource::Iron;
                else if (roll < 8) r = Resource::Coal;
                else if (roll < 12) r = Resource::Horses;
                else if (roll < 16) r = Resource::Rocks;
            }

            if (r != Resource::Nothing)
            {
                map[y][x]->~Tile();
                map[y][x] = new Tile(t, r);
            }
        }
    }
}

void Game::showMainMenu() {
    int choise;
    do {
        clearScreen();
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

======================================================================================================================================================
1 | Start Game
2 | Controls
0 | Exit
------------------------------------------------------------------------------------------------------------------------------------------------------
> )");
        std::cin >> choise;
        if (std::cin.fail()) {
            fmt::print(fg(COLOR1), "Ошибка: введите число!\n");

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choise = -1;
        }
        else if (choise < 0 || choise > 2)
        {
            fmt::print(fg(COLOR1), "Ошибка: введите 0-2\n");
            choise = -1;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } while (choise == -1);
    switch (choise) {
        case 0:
            exit(0);
            break;
        case 1:
            this->startGame();
            break;
        case 2:
            this->printControls();
            break;
        default:
            break;
    }
}

void Game::startGame() {
    this->generateMap();
    this->playerTurn();
}

void Game::printStats() {
    fmt::print(fg(COLOR_GOLD), "o Gold: ");
    fmt::print(fg(COLOR_SCIENCE), "Δ Science: \n");
    for (const auto& pair : this->player->getResources())
    {
        Resource key = pair.first;
        int value = pair.second;

        fmt::print(fg(resource_fg.at(key)), "{} {}: {}", resource_icons.at(key), resource_names.at(key), value);
    }
}

void Game::printControls() {}

void Game::playerTurn() {
    clearScreen();
    printStats();
    this->printMap();
}

