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
#include <iomanip>


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

Civilization* Game::getPlayer() const {
    return this->player;
}
Tile* Game::getTile(int x, int y) const {
    if (x < 0 || x >= MAP_SIZE_X || y < 0 || y >= MAP_SIZE_Y)
    {
        return nullptr;
    }
    return map[y][x];
}
MapView Game::getMapView() const {
    return this->mapView;
}
int Game::getSelectedTileX() const {
    return this->selectedTileX;
}
int Game::getSelectedTileY() const {
    return this->selectedTileY;
}
Tile* Game::getSelectedTile() const {
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
                new Unit(u_warrior, ux, uy, this);
                this->selectedTileX = x;
                this->selectedTileY = y;
            }
        }
    } while (city == nullptr);
}

void Game::showMainMenu() {
    int choice;
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
        std::cin >> choice;
        if (std::cin.fail()) {
            fmt::print(fg(COLOR1), "Ошибка: введите число!\n");

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1;
        }
        else if (choice < 0 || choice > 2)
        {
            fmt::print(fg(COLOR1), "Ошибка: введите 0-2\n");
            choice = -1;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } while (choice == -1 || choice == 2);
    switch (choice) {
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
        for (City* city : this->player->getCities()) {
            city->update();
        }
        for (Unit* unit : player->getUnits()) {
            unit->update(this);
        }
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
        fmt::print(fg(COLOR2) | bg(COLOR4), "Choose your aciton (Type \"c\" to see controls list) >");
        std::getline(std::cin, action);
        if (action == "w") {
            this->moveSelect(0, -1);
        }
        else if (action == "s") {
            this->moveSelect(0, 1);
        }
        else if (action == "a") {
            this->moveSelect(-1, 0);
        }
        else if (action == "d") {
            this->moveSelect(1, 0);
        }
        else if (action == "p") {
            std::string choice;
            fmt::print(fg(COLOR2) | bg(COLOR4), "Are you sure you want to leave the game? (Y/n) >");
            std::getline(std::cin, choice);
            if (choice == "Y") {
                exit(0);
            }
        }
        else if (action == "m") {
            int choice;
            fmt::print(fg(COLOR2) | bg(COLOR4), "What view of map you want change to? (1 - Terrain, 2 - Politic, 3 - Units, 4 - Basic) >");
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
        else if (action == "r") {
            int choice;
            std::string text = "Research Menu";

            int width = MAP_SIZE_X * 3;
            int padding = (width - text.size()) / 2;

            text.insert(0, padding, ' ');
            text.append(width - text.size(), ' ');
            clearScreen();
            fmt::print(fg(COLOR2) | bg(COLOR4), "{}\n", text);
            this->printResearchTable();
            do {
                fmt::print(fg(COLOR2) | bg(COLOR4), "Enter number of building/unit you want to research or leave this menu using 0 >");
                std::cin >> choice;
                if (std::cin.fail()) {
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Error: enter a number!\n");

                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    choice = -1;
                    continue;
                }
                if (choice < 0 || choice > u_list.size() + b_list.size() - this->player->getResearchedUnits().size() - this->player->getResearchedBuildings().size()) {
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Error: enter a number between 0 and {}!\n", u_list.size() + b_list.size() - this->player->getResearchedBuildings().size() - this->player->getResearchedUnits().size());
                    continue;
                }

                int counter = 1;
                bool isFound = false;

                for (int i = 0; i < b_list.size(); i++)
                {
                    bool isResearched = false;

                    for (Building* researched : player->getResearchedBuildings())
                    {
                        if (researched->getName() == b_list[i].getName())
                        {
                            isResearched = true;
                            break;
                        }
                    }

                    if (isResearched) {
                        continue;
                    }

                    if (counter == choice)
                    {
                        Building* building = new Building(b_list[i]);
                        if (this->player->researchBuilding(building, building->getResearchCost())) {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "Building researched!\n");
                            choice = 0;
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                        } else {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "Not enough science!\n");
                        }
                        isFound = true;
                        break;
                    }

                    counter++;
                }
                for (int i = 0; i < u_list.size() && !isFound; i++)
                {
                    bool isResearched = false;

                    for (Unit* researched : player->getResearchedUnits())
                    {
                        if (researched->getName() == u_list[i].getName())
                        {
                            isResearched = true;
                            break;
                        }
                    }

                    if (isResearched)
                        continue;

                    if (counter == choice)
                    {
                        Unit* unit = new Unit(u_list[i]);
                        if (this->player->researchUnit(unit, unit->getResearchCost())) {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "Unit researched!\n");
                            choice = 0;
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                        } else {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "Not enough science!\n");
                        }
                        break;
                    }

                    counter++;
                }
            } while (choice != 0);
        }
        else if (action == "e") {
            Tile* t = this->getSelectedTile();
            if (t->getUnit() != nullptr) {
                Unit* unit = t->getUnit();
                std::string choice;
                int result = 0;
                do {
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Choose direction of move (w/a/s/d/0) >");
                    std::getline(std::cin, choice);
                    if (choice == "w") {
                        result = unit->move(unit->getX(), unit->getY()-1, this);
                        this->moveSelect(0, -1);
                    }
                    else if (choice == "a") {
                        result = unit->move(unit->getX()-1, unit->getY(), this);
                        this->moveSelect(-1, 0);
                    }
                    else if (choice == "s") {
                        result = unit->move(unit->getX(), unit->getY()+1, this);
                        this->moveSelect(0, 1);
                    }
                    else if (choice == "d") {
                        result = unit->move(unit->getX()+1, unit->getY(), this);
                        this->moveSelect(1, 0);
                    }
                    if (result != 0) {
                        if (result == 1) {
                            break;
                        }
                        if (result == -1) {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "Tile is already occupied by unit!");
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            break;
                        }
                        if (result == -2) {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "Tile has a city!");
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            break;
                        }
                        if (result == -3) {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "You can't go on territory of a citystate without declaring a war!");
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            break;
                        }
                        if (result == -4) {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "Can't go on terrain of this type!");
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            break;
                        }
                        if (result == -5) {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "Error! Can't check movement cost.");
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            break;
                        }
                        if (result == -6) {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "Error! Distance is too big.");
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            break;
                        }
                        if (result == -7) {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "Error! Can't find tile.");
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            break;
                        }
                        if (result == -8) {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "Not enough movement point!");
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            break;
                        }
                    }
                } while (choice != "0");
            }
        }
        else if (action == "q") {
            Tile* t = this->getSelectedTile();
            if (t->getOwner() != nullptr && t->getBuilding() == nullptr) {
                int choice = -1;
                do {
                    int counter = 1;
                    for (Building* b : this->player->getResearchedBuildings()) {
                        fmt::print(fg(COLOR2) | bg(COLOR4), "{} | {}, cost: {} gold\n", counter, b->getName(), b->getCost());
                        counter++;
                    }
                    fmt::print(fg(COLOR2) | bg(COLOR4), "Enter number of building you want to build (0 to leave this menu) >");

                    std::cin >> choice;

                    if (std::cin.fail()) {
                        fmt::print(fg(COLOR2) | bg(COLOR4), "Error: enter a number!\n");

                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        choice = -1;
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        continue;
                    }

                    if (choice > 0 && choice <= this->player->getResearchedBuildings().size()) {
                        Building* building = this->player->getResearchedBuildings()[choice-1];
                        if (building->getCost() > this->player->getGold()) {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "You don't have enough gold!\n");
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            continue;
                        }

                        bool isTerrainSuitable = false;
                        for (TerrainType terr : building->getRequiredTerrain()) {
                            if (terr == t->getTerrain()) {
                                isTerrainSuitable = true;
                                break;
                            }
                        }
                        bool isResourceSuitable = building->getRequiredResource() == t->getResource() || building->getRequiredResource() == Resource::Nothing;

                        if (!isTerrainSuitable || !isResourceSuitable) {
                            fmt::print(fg(COLOR2) | bg(COLOR4), "You can't place it here!\n");
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            continue;
                        }

                        this->player->removeGold(building->getCost());
                        t->setBuilding(new Building(building));
                        fmt::print(fg(COLOR2) | bg(COLOR4), "Building successfully built!");
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        choice = 0;
                    }
                } while (choice != 0);
            } else {
                fmt::print(fg(COLOR2) | bg(COLOR4), "Can't build on foreign territory\n");
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
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

void Game::printResearchTable()
{
    int counter = 1;

    int tableWidth = MAP_SIZE_X * 3;

    int w_name = 14;
    int w_type = 12;
    int w_num = 10;
    int w_cost = 13;
    int w_res = 12;
    int w_research = 10;
    int w_req_res = 8;
    int used = w_name + w_type + w_num * 5 + w_cost + w_res + w_research + w_req_res + 12;
    int w_terr = std::max(10, tableWidth - used);

    auto cut = [](const std::string& s, int w) -> std::string
    {
        if (w <= 1) return std::string("…");
        if ((int)s.size() <= w) return s;
        return s.substr(0, w - 1) + "…";
    };

    fmt::print(fg(COLOR2) | bg(COLOR4), "{}\n", std::string(tableWidth, '-'));
    fmt::print(fg(COLOR2) | bg(COLOR4), "   | {:<{}} | {:<{}} | {:>{}} | {:>{}} | {:>{}} | {:>{}} | {:>{}} | {:>{}} | {:>{}} | {:<{}} |\n",
    "Name", w_name,
    "Type", w_type,
    "Food", w_num,
    "Gold", w_num,
    "Population",  w_num,
    "Sciecne",  w_num,
    "Resource",  w_num,
    "Science Cost", w_cost,
    "Req. res", w_req_res,
    "Terrain", w_terr
    );

    for (const auto& b : b_list)
    {
        std::string terrainStr;

        for (auto t : b.getRequiredTerrain())
            terrainStr += terrain_icons.at(t) + " ";

        std::string b_type = "Unknown";

        switch (b.getType()) {
            case BuildingType::City:
                continue;
            case BuildingType::Economy:
                b_type = "Economy";
                break;
            case BuildingType::Production:
                b_type = "Production";
                break;
            case BuildingType::Military:
                b_type = "Military";
                break;
            case BuildingType::Science:
                b_type = "Science";
                break;
            default:
                break;
        }

        bool isResearched = false;
        for (Building* researched_building : this->player->getResearchedBuildings()) {
            if (researched_building->getName() == b.getName()) {
                isResearched = true;
                break;
            }
        }
        if (isResearched) {
            continue;
        }

        fmt::print(
            fg(COLOR2) | bg(COLOR4), "{:<2} | {:<{}} | {:<{}} | {:>{}} | {:>{}} | {:>{}} | {:>{}} | {:>{}} | {:>{}} | {:>{}} | {:<{}} |\n",
            counter,
            cut(b.getName(), w_name), w_name,
            cut(b_type, w_type), w_type,

            b.getFoodBonus(), w_num,
            b.getGoldBonus(), w_num,
            b.getPopulationBonus(), w_num,
            b.getScienceBonus(), w_num,
            b.getResourceBonus(), w_num,

            b.getResearchCost(), w_cost,
            resource_names.at(b.getRequiredResource()), w_req_res,
            cut(terrainStr, w_terr), w_terr
        );
        counter++;
    }

    fmt::print(fg(COLOR2) | bg(COLOR4), "{}\n", std::string(tableWidth, '-'));

    auto formatResources = [](const std::map<Resource, int>& req) -> std::string
    {
        std::string res;
        for (auto& [r, v] : req)
        {
            if (v <= 0) continue;
            res += resource_names.at(r) + ":" + std::to_string(v) + " ";
        }
        if (res.empty()) return " ";
        return res;
    };


    fmt::print(fg(COLOR2) | bg(COLOR4),
"   | {:<{}} | {:<{}} | {:>{}} | {:>{}} | {:>{}} | {:>{}} | {:>{}} | {:<{}} | {:<{}} |\n",
    "Name", w_name,
    "Type", w_type,
    "HP", w_num,
    "Damage", w_num,
    "Movement", w_num,
    "Range", w_num,
    "Science cost", w_cost,
    "Req.Building", w_res,
    "Req.Resources", w_terr + 9
    );

    for (const auto& u : u_list)
    {
        std::string u_type;

        switch (u.getType())
        {
            case UnitType::Melee:
                u_type = "Melee";
                break;
            case UnitType::Ranged:
                u_type = "Ranged";
                break;
            case UnitType::Cavalry:
                u_type = "Cavlary";
                break;
            case UnitType::AntiCavalry:
                u_type = "AntiCavlary";
                break;
            case UnitType::Siege:
                u_type = "Siege";
                break;
            case UnitType::Naval:
                u_type = "Naval";
                break;
            default:
                u_type = "Unknown";
                break;
        }

        bool isResearched = false;
        for (Unit* researched_unit : this->player->getResearchedUnits()) {
            if (researched_unit->getName() == u.getName()) {
                isResearched = true;
                break;
            }
        }
        if (isResearched) {
            continue;
        }

        std::string reqRes = formatResources(u.getRequiredResources());

        std::string reqBuild = u.getRequiredBuilding()
            ? u.getRequiredBuilding()->getName()
            : " ";

        fmt::print(fg(COLOR2) | bg(COLOR4),
            "{:<2} | {:<{}} | {:<{}} | {:>{}} | {:>{}} | {:>{}} | {:>{}} | {:>{}} | {:<{}} | {:<{}} |\n",

            counter,
            cut(u.getName(), w_name), w_name,
            cut(u_type, w_type), w_type,

            u.getMaxHealth(), w_num,
            u.getDamage(), w_num,
            u.getMaxMovement(), w_num,
            u.getRange(), w_num,

            u.getResearchCost(), w_cost,
            cut(reqBuild, w_res), w_res,
            cut(reqRes, w_terr), w_terr+9
        );
        counter++;
    }

    fmt::print(fg(COLOR2) | bg(COLOR4), "{}\n", std::string(tableWidth, '-'));
}