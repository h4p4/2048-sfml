#pragma once
#include <2048Game/StateBase.hpp>
#include <2048Game/Tile.hpp>


class GameState : public StateBase 
{
private:
    const sf::Color emptyTileColor = sf::Color(205, 193, 180);

    std::vector<std::vector<Tile>> tiles;
    std::vector<std::vector<Tile>> backgroundTiles;
    std::vector<Tile*> pEmptyTiles;
    int gridSize;

    void generateRandomPlacedTile();
    void drawTile(Tile &rTile);

    void moveAllTilesRight();
    void moveAllTilesLeft();
    void moveAllTilesUp();
    void moveAllTilesDown();

    void findEmptyTiles();
public:
    GameState(sf::RenderWindow &rWindow);
    ~GameState();
    bool init();
    void updateEvents(sf::Event &rEvent);
    void update();
    void clear();
    void destroy();

};

