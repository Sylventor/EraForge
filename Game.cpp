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
#include <string>

#include "Game.h"

#include "Civilization.h"
#include "Tile.h"
#include "City.h"

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
    this->player = new Civilization(300, {new Building(b_farm)}, {new Unit(u_warrior)});
    this->mapView = MapView::Base;
    this->generateMap();
}

void Game::clearMap() {
    for (int y = 0; y < MAP_SIZE_Y; y++) {
        for (int x = 0; x < MAP_SIZE_X; x++) {
            if (map[y][x] == nullptr) continue;

            delete map[y][x];
            map[y][x] = nullptr;
        }
    }
}

Civilization* const Game::getPlayer() {
    return this->player;
}
Tile* const Game::getTile(int x, int y) {
    return this->map[y][x];
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

void Game::printSelectedTile() {
    Tile* t = this->getTile(this->selectedTileX, this->selectedTileY);
    if (t != nullptr && t->getRevealed()) {
        if (t->getBuilding() != nullptr) {
            Building* b = t->getBuilding();
            BuildingType type = b->getType();
            switch (type) {
                case BuildingType::City:
                    if (t->getOwner() != nullptr) {
                        City* c = t->getOwner();
                        fmt::print(fg(COLOR2) | bg(COLOR4), "City {}, population: {}, food: {}, health {}/{}", c->getName(), c->getPopulation(), c->getFood(), c->getHealth(), c->getMaxHealth());
                    } else if (t->getCitystateOwner() != nullptr) {
                        Citystate* c = t->getCitystateOwner();\
                        std::string ctype;
                        switch (c->getType()) {
                            case CitystateType::Economic:
                                ctype = "Economic";
                                break;
                            case CitystateType::Military:
                                ctype = "Military";
                                break;
                            case CitystateType::Science:
                                ctype = "Science";
                                break;
                            default:
                                ctype = "Unknown";
                                break;
                        }
                        fmt::print(fg(COLOR2) | bg(COLOR4), "Citystate {}, type: {}, health {}/{}", c->getName(), ctype, c->getHealth(), c->getMaxHealth());
                    }
                    break;
                case BuildingType::Economy:
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Building {}, type: Economy, food bonus: {}, population bonus: {}, gold bonus: {}, science bonus: {}, resource bonus: {}", b->getName(), b->getFoodBonus(), b->getPopulationBonus(), b->getGoldBonus(), b->getScienceBonus(), b->getResourceBonus());
                    break;
                case BuildingType::Science:
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Building {}, type: Science, food bonus: {}, population bonus: {}, gold bonus: {}, science bonus: {}, resource bonus: {}", b->getName(), b->getFoodBonus(), b->getPopulationBonus(), b->getGoldBonus(), b->getScienceBonus(), b->getResourceBonus());
                    break;
                case BuildingType::Military:
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Building {}, type: Military, food bonus: {}, population bonus: {}, gold bonus: {}, science bonus: {}, resource bonus: {}", b->getName(), b->getFoodBonus(), b->getPopulationBonus(), b->getGoldBonus(), b->getScienceBonus(), b->getResourceBonus());
                    break;
                case BuildingType::Production:
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Building {}, type: Production, food bonus: {}, population bonus: {}, gold bonus: {}, science bonus: {}, resource bonus: {}", b->getName(), b->getFoodBonus(), b->getPopulationBonus(), b->getGoldBonus(), b->getScienceBonus(), b->getResourceBonus());
                    break;
                default:
                    break;
            }
            std::cout << std::endl;
        }
        if (t->getUnit() != nullptr) {
            Unit* u = t->getUnit();
            UnitType type = u->getType();
            switch (type) {
                case UnitType::Melee:
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Unit {}, type: Melee, health: {}/{}, range: {}, movement points: {}/{}, damage: {}", u->getName(), u->getHealth(), u->getMaxHealth(), u->getRange(), u->getMovement(), u->getMaxMovement(), u->getDamage());
                    break;
                case UnitType::Cavalry:
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Unit {}, type: Cavalry, health: {}/{}, range: {}, movement points: {}/{}, damage: {}", u->getName(), u->getHealth(), u->getMaxHealth(), u->getRange(), u->getMovement(), u->getMaxMovement(), u->getDamage());
                    break;
                case UnitType::AntiCavalry:
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Unit {}, type: AntiCavalry, health: {}/{}, range: {}, movement points: {}/{}, damage: {}", u->getName(), u->getHealth(), u->getMaxHealth(), u->getRange(), u->getMovement(), u->getMaxMovement(), u->getDamage());
                    break;
                case UnitType::Naval:
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Unit {}, type: Naval, health: {}/{}, range: {}, movement points: {}/{}, damage: {}", u->getName(), u->getHealth(), u->getMaxHealth(), u->getRange(), u->getMovement(), u->getMaxMovement(), u->getDamage());
                    break;
                case UnitType::Siege:
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Unit {}, type: Siege, health: {}/{}, range: {}, movement points: {}/{}, damage: {}", u->getName(), u->getHealth(), u->getMaxHealth(), u->getRange(), u->getMovement(), u->getMaxMovement(), u->getDamage());
                    break;
                case UnitType::Ranged:
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Unit {}, type: Ranged, health: {}/{}, range: {}, movement points: {}/{}, damage: {}", u->getName(), u->getHealth(), u->getMaxHealth(), u->getRange(), u->getMovement(), u->getMaxMovement(), u->getDamage());
                    break;
                default:
                    break;
            }
            std::cout << std::endl;
        }
        std::string owner = "Free";
        if (t->getOwner() != nullptr) {
            owner = t->getOwner()->getName();
        } else if (t->getCitystateOwner() != nullptr) {
            owner = t->getCitystateOwner()->getName();
        }
        std::string terrain = "Unkonown";
        std::string resource = "Nothing";
        switch (t->getTerrain()) {
            case TerrainType::Plains:
                terrain = "Plains";
                break;
            case TerrainType::Desert:
                terrain = "Desert";
                break;
            case TerrainType::Forest:
                terrain = "Forest";
                break;
            case TerrainType::Mountains:
                terrain = "Mountains";
                break;
            case TerrainType::Ocean:
                terrain = "Ocean";
                break;
            case TerrainType::Rivers:
                terrain = "Rivers";
                break;
            case TerrainType::Shallow:
                terrain = "Shallow";
                break;
            default:
                break;
        }
        switch (t->getResource()) {
            case Resource::Coal:
                resource = "Coal";
                break;
            case Resource::Horses:
                resource = "Horses";
                break;
            case Resource::Iron:
                resource = "Iron";
                break;
            case Resource::Nothing:
                resource = "Nothing";
                break;
            case Resource::Rocks:
                resource = "Rocks";
                break;
        }
        fmt::print(fg(COLOR2) | bg(COLOR4), "Owner: {}, terrain: {}, resource: {}", owner, terrain, resource);
        std::cout << std::endl;
    }
}

void Game::printMap() {
    for (int y = 0; y < MAP_SIZE_Y; y++) {
        for (int x = 0; x < MAP_SIZE_X; x++) {
            if (x == selectedTileX && y == selectedTileY) {
                this->map[y][x]->printTile(this->mapView, true);
            } else {
                this->map[y][x]->printTile(this->mapView, false);
            }
        }
        fmt::print("\n");
    }
}

void Game::generateMap()
{
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

        delete map[y][x];
        map[y][x] = new Tile(TerrainType::Mountains, Resource::Nothing);
    }

    // 5. РЕКИ (из гор к воде)
    for (int i = 0; i < 1000; i++)
    {
        int x = rand() % MAP_SIZE_X;
        int y = rand() % MAP_SIZE_Y;

        if (map[y][x]->getTerrain() != TerrainType::Mountains)
            continue;

        for (int step = 0; step < 60; step++)
        {
            delete map[y][x];
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
    // Проверка на то, что хотя-бы 1 река сгенерировалась
    bool has_rivers = false;
    for (int y = 0; y < MAP_SIZE_Y && !has_rivers; y++) {
        for (int x = 0; x < MAP_SIZE_X && !has_rivers; x++) {
            if (this->getTile(x, y)->getTerrain() == TerrainType::Rivers) {
                has_rivers = true;
            }
        }
    }
    if (!has_rivers) {
        this->clearMap();
        return this->generateMap();
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
                    delete map[ny][nx];
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
                    delete map[ny][nx];
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
                delete map[y][x];
                map[y][x] = new Tile(t, r);
            }
        }
    }

    // 9. Генрация города
    City* city = nullptr;
    do {
        int x = rand() % MAP_SIZE_X;
        int y = rand() % MAP_SIZE_Y;

        if (map[y][x]->getTerrain() == TerrainType::Rivers) {
            int roll = rand() % 100;
            if (roll < 10) {
                city = new City(this, player, x, y, "Test");
                int ux = -1;
                int uy = -1;
                for (int nx = -1; nx <= 1; nx++) {
                    for (int ny = -1; ny <= 1; ny++) {
                        if (inBounds(x+nx, y+ny)) {
                            Tile* t = this->getTile(x+nx, y+ny);
                            if ((t->getTerrain() == TerrainType::Rivers || t->getTerrain() == TerrainType::Desert || t->getTerrain() == TerrainType::Plains || t->getTerrain() == TerrainType::Forest) && !t->getBuilding()) {
                                ux = x+nx;
                                uy = y+ny;
                            }
                        }
                    }
                }
                if (ux == -1 || uy == -1) {
                    this->clearMap();
                    return this->generateMap();
                }
                Unit* startUnit = new Unit(u_warrior, ux, uy, this);
                this->selectedTileX = x;
                this->selectedTileY = y;
            }
        }
    } while (city == nullptr);
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
    } while (choise == -1 || choise == 2);
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
    while (true) {
        this->playerTurn();
    }
}

void Game::printStats() {
    fmt::print(fg(COLOR_GOLD) | bg(COLOR4),"o Gold: {} ", this->player->getGold());
    fmt::print(fg(COLOR_SCIENCE) | bg(COLOR4), "Δ Science: {}", this->player->getScience());
    int printed = fmt::format("o Gold: {} ", this->player->getGold()).size()
            + fmt::format("Δ Science: {}", this->player->getScience()).size();
    for (const auto& pair : this->player->getResources())
    {
        Resource key = pair.first;
        int value = pair.second;

        fmt::print(fg(resource_fg.at(key)) | bg(COLOR4), "{} {}: {}", resource_icons.at(key), resource_names.at(key), value);
        printed += fmt::format("{} {}: {} ", resource_icons.at(key), resource_names.at(key), value).size();
    }
    fmt::print(bg(COLOR4), "{}\n", std::string(MAP_SIZE_X*3 + 1 - printed, ' '));
}

void Game::printControls() {}

void Game::playerTurn() {
    std::string action;
    do {
        clearScreen();
        printStats();
        this->printMap();
        printSelectedTile();
        fmt::print(fg(COLOR2) | bg(COLOR4), "Choose your aciton (Type \"c\" to see controls list) > ");
        std::getline(std::cin, action);
        if (action == "w") {
            this->moveSelect(0, -1);
        } else if (action == "s") {
            this->moveSelect(0, 1);
        } else if (action == "a") {
            this->moveSelect(-1, 0);
        } else if (action == "d") {
            this->moveSelect(1, 0);
        } else if (action == "q") {
            std::string choice;
            fmt::print(fg(COLOR2) | bg(COLOR4), "Are you sure you want to leave the game? (Y/n) > ");
            std::getline(std::cin, choice);
            if (choice == "Y") {
                exit(0);
            }
        } else if (action == "m") {
            int choice;
            fmt::print(fg(COLOR2) | bg(COLOR4), "What view of map you want change to? (1 - Terrain, 2 - Politic, 3 - Units, 4 - Basic) > ");
            std::cin >> choice;
            switch (choice) {
                case 1:
                    this->mapView = MapView::Terrain;
                    break;
                case 2:
                    this->mapView = MapView::Politic;
                    break;
                case 3:
                    this->mapView = MapView::Units;
                    break;
                case 4:
                    this->mapView = MapView::Base;
                    break;
            }
            std::cin.ignore();
        }
    } while (action != "0");
}

void Game::moveSelect(int dx, int dy) {
    int nx = this->selectedTileX + dx;
    int ny = this->selectedTileY + dy;
    if (nx >= 0 && nx < MAP_SIZE_X) {
        this->selectedTileX = nx;
    } else if (nx < 0) {
        this->selectedTileX = MAP_SIZE_X-1;
    } else if (nx >= MAP_SIZE_X) {
        this->selectedTileX = 0;
    }
    if (ny >= 0 && ny < MAP_SIZE_Y) {
        this->selectedTileY = ny;
    } else if (ny < 0) {
        this->selectedTileY = MAP_SIZE_Y-1;
    } else if (ny >= MAP_SIZE_Y) {
        this->selectedTileY = 0;
    }
}
