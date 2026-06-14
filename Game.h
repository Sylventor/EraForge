//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H

#include "Globals.h"

class Civilization;
class Tile;
class Citystate;

class Game {
private:
    Civilization* player;
    Tile* map[MAP_SIZE_Y][MAP_SIZE_X];
    MapView mapView;
    int selectedTileX;
    int selectedTileY;
public:
    Game();

    Civilization* const getPlayer();
    Tile* const getTile(int x, int y);
    MapView const getMapView();
    int const getSelectedTileX();
    int const getSelectedTileY();
    Tile* const getSelectedTile();


    void printMap();
    void generateMap();
    void startGame();
    void playerTurn();
    void aiTurn();
    void declareWar(Citystate* citystate);
    void showMainMenu();
    void printControls();
    void buildCity(int x, int y);
    void moveSelect(int x, int y);
};


#endif //UNTITLED_GAME_H
