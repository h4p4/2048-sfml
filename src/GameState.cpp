#include <2048Game/GameState.hpp>

GameState::GameState(sf::RenderWindow &rWindow) : StateBase(rWindow), gridSize(4)
{
    this->init();
}

GameState::~GameState()
{
    this->clear();
}

void GameState::findEmptyTiles()
{
    pEmptyTiles.clear();
    for (size_t i = 0; i < gridSize; i++)
        for (size_t j = 0; j < gridSize; j++)
            if (tiles[i][j].isEmpty())
                pEmptyTiles.push_back(&tiles[i][j]);
}

void GameState::generateRandomPlacedTile()
{
    findEmptyTiles();
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, pEmptyTiles.size() - 1);
    Tile *pTile = pEmptyTiles.at(dist(rng));
    pTile->setFillColor(sf::Color(238, 228, 218));
    pTile->setInsideNumber(2);
}

void GameState::drawTile(Tile &rTile)
{
    window.draw(rTile);
    if (rTile.getInsideNumberText()->getString().toAnsiString() != "0")
        window.draw(*(rTile.getInsideNumberText()));
}

void GameState::moveAllTiles(MoveDirection direction)
{
    for (size_t y = 0; y < gridSize; y++)
    {
        bool wereMerged = false;
        if (direction == MoveDirection::Left || direction == MoveDirection::Up)
            for (size_t prevCol = 1; prevCol != gridSize; prevCol++)
                for (size_t col = 0; col != gridSize - 1; col++)
                {
                    if (direction == MoveDirection::Left)
                    {
                        trySwapTiles(&tiles[prevCol][y], &tiles[col][y], prevCol, y);
                        if (!wereMerged && tryMergeTiles(&tiles[col + 1][y], &tiles[col][y], (col + 1), y, col != std::numeric_limits<size_t>::max()))
                            wereMerged = true;
                        continue;
                    }
                    // UP
                    trySwapTiles(&tiles[y][prevCol], &tiles[y][col], y, prevCol);
                    if (!wereMerged && tryMergeTiles(&tiles[y][col + 1], &tiles[y][col], y, (col + 1), col != std::numeric_limits<size_t>::max()))
                        wereMerged = true;
                }
        if (direction == MoveDirection::Right || direction == MoveDirection::Down)
            for (size_t prevCol = gridSize - 2; prevCol != std::numeric_limits<size_t>::max(); prevCol--)
                for (size_t col = gridSize - 1; col > 0; col--)
                {
                    if (direction == MoveDirection::Right)
                    {
                        trySwapTiles(&tiles[prevCol][y], &tiles[col][y], prevCol, y);
                        if (!wereMerged && tryMergeTiles(&tiles[col - 1][y], &tiles[col][y], (col - 1), y, col < gridSize))
                            wereMerged = true;
                        continue;
                    }
                    // DOWN
                    trySwapTiles(&tiles[y][prevCol], &tiles[y][col], y, prevCol);
                    if (!wereMerged && tryMergeTiles(&tiles[y][col - 1], &tiles[y][col], y, (col - 1), col < gridSize))
                        wereMerged = true;
                }
    }
}

bool GameState::trySwapTiles(Tile *firstTile, Tile *secondTile, size_t col, size_t y)
{
    if (!((*firstTile).getFillColor() != emptyTileColor && (*secondTile).getFillColor() == emptyTileColor))
        return false;
    (*firstTile).replace((*secondTile).getPosition().x, (*secondTile).getPosition().y);
    *secondTile = *(new Tile(*firstTile));
    *firstTile = *(new Tile(200 * col + 50, 200 * y + 50, 0, emptyTileColor));
    return true;
}

bool GameState::tryMergeTiles(Tile *firstTile, Tile *secondTile, size_t col, size_t y, bool condition)
{
    if (!(condition && *(*firstTile).getInsideNumber() == *(*secondTile).getInsideNumber() &&
          *(*firstTile).getInsideNumber() != 0))
        return false;
    (*firstTile).replace((*secondTile).getPosition().x, (*secondTile).getPosition().y);
    *secondTile = *(new Tile(*firstTile));
    (*secondTile).doubleTheNum();
    *firstTile = *(new Tile(200 * col + 50, 200 * y + 50, 0, emptyTileColor));
    return true;
}

bool GameState::init()
{
    Tile::loadFont();
    for (size_t i = 0; i < gridSize; i++)
    {
        std::vector<Tile> innerTiles;
        for (size_t j = 0; j < gridSize; j++)
        {
            Tile *tile = new Tile(200 * i + 50, 200 * j + 50, 0, emptyTileColor);
            innerTiles.push_back(*tile);
            pEmptyTiles.push_back(tile);
        }
        backgroundTiles.push_back(innerTiles);
        tiles.push_back(innerTiles);
    }
    generateRandomPlacedTile();
    generateRandomPlacedTile();
    return true;
}

void GameState::clear()
{
    for (size_t i = 0; i < gridSize; i++)
    {
        tiles[i].clear();
        backgroundTiles[i].clear();
    }
    pEmptyTiles.clear();
    tiles.clear();
    backgroundTiles.clear();
}

void GameState::updateEvents(sf::Event &rEvent)
{
    if (rEvent.type == sf::Event::EventType::KeyPressed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            this->exitState(); // -- ВЫХОД ИЗ СОСТОЯНИЯ --

        // -- ПЕРЕМЕЩЕНИЕ Tile-ов
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                moveAllTiles(MoveDirection::Right);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                moveAllTiles(MoveDirection::Left);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                moveAllTiles(MoveDirection::Up);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                moveAllTiles(MoveDirection::Down);
            generateRandomPlacedTile();
        }
    }
}

void GameState::update()
{
    window.clear(sf::Color(187, 173, 160));
    for (size_t i = 0; i < gridSize; i++)
        for (size_t j = 0; j < gridSize; j++)
        {
            drawTile(backgroundTiles[i][j]);
            drawTile(tiles[i][j]);
        }
}