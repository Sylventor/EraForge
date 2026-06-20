//
// Created by Nikita on 28.05.2026.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H

#include "Types.h"


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

    void clearMap();
public:
    Game();

    Civilization* getPlayer() const;
    Tile* getTile(int x, int y) const;
    MapView getMapView() const;
    int getSelectedTileX() const;
    int getSelectedTileY() const;
    Tile* getSelectedTile() const;


    void printMap();
    void printSelectedTile();
    void printStats();
    void printResearchTable();
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
