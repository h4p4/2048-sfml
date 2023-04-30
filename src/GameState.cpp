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

void GameState::moveAllTilesLeft()
{
    for (size_t y = 0; y < gridSize; y++)
    {
        bool wereMerged = false;
        for (size_t prevCol = 1; prevCol != gridSize; prevCol++)
        {
            for (size_t col = 0; col != gridSize - 1; col++)
            {
                if (tiles[prevCol][y].getFillColor() != emptyTileColor && tiles[col][y].getFillColor() == emptyTileColor)
                {
                    tiles[prevCol][y].replace(tiles[col][y].getPosition().x, tiles[col][y].getPosition().y);
                    tiles[col][y] = *(new Tile(tiles[prevCol][y]));
                    tiles[prevCol][y] = *(new Tile(200 * prevCol + 50, 200 * y + 50, 0, emptyTileColor));
                }

                if (col != std::numeric_limits<size_t>::max() &&
                    *tiles[col + 1][y].getInsideNumber() == *tiles[col][y].getInsideNumber() &&
                    *tiles[col + 1][y].getInsideNumber() != 0 &&
                    !wereMerged)
                {
                    tiles[col + 1][y].replace(tiles[col][y].getPosition().x, tiles[col][y].getPosition().y);
                    tiles[col][y] = *(new Tile(tiles[col + 1][y]));
                    tiles[col][y].doubleTheNum();
                    tiles[col + 1][y] = *(new Tile(200 * (col + 1) + 50, 200 * y + 50, 0, emptyTileColor));
                    wereMerged = true;
                }
            }
        }
    }
}

void GameState::moveAllTilesRight()
{
    for (size_t y = 0; y < gridSize; y++)
    {
        bool wereMerged = false;
        for (size_t prevCol = gridSize - 2; prevCol != std::numeric_limits<size_t>::max(); prevCol--)
        {
            for (size_t col = gridSize - 1; col > 0; col--)
            {
                if (tiles[prevCol][y].getFillColor() != emptyTileColor && tiles[col][y].getFillColor() == emptyTileColor)
                {
                    tiles[prevCol][y].replace(tiles[col][y].getPosition().x, tiles[col][y].getPosition().y);
                    tiles[col][y] = *(new Tile(tiles[prevCol][y]));
                    tiles[prevCol][y] = *(new Tile(200 * prevCol + 50, 200 * y + 50, 0, emptyTileColor));
                }

                // где нибудь здесь запускать анимацию

                if (col < gridSize &&
                    *tiles[col - 1][y].getInsideNumber() == *tiles[col][y].getInsideNumber() &&
                    *tiles[col - 1][y].getInsideNumber() != 0 && // если обе клетки равны и обе не ноль (не пустая)
                    !wereMerged)
                {
                    tiles[col - 1][y].replace(tiles[col][y].getPosition().x, tiles[col][y].getPosition().y);
                    tiles[col][y] = *(new Tile(tiles[col - 1][y]));
                    tiles[col][y].doubleTheNum();
                    tiles[col - 1][y] = *(new Tile(200 * (col - 1) + 50, 200 * y + 50, 0, emptyTileColor));
                    wereMerged = true;
                }
            }
        }
    }
}

void GameState::moveAllTilesUp()
{
    for (size_t y = 0; y < gridSize; y++)
    {
        bool wereMerged = false;
        for (size_t prevCol = 1; prevCol != gridSize; prevCol++)
        {
            for (size_t col = 0; col != gridSize - 1; col++)
            {
                if (tiles[y][prevCol].getFillColor() != emptyTileColor && tiles[y][col].getFillColor() == emptyTileColor)
                {
                    tiles[y][prevCol].replace(tiles[y][col].getPosition().x, tiles[y][col].getPosition().y);
                    tiles[y][col] = *(new Tile(tiles[y][prevCol]));
                    tiles[y][prevCol] = *(new Tile(200 * y + 50, 200 * prevCol + 50, 0, emptyTileColor));
                }
                if (col != std::numeric_limits<size_t>::max() &&
                    *tiles[y][col + 1].getInsideNumber() == *tiles[y][col].getInsideNumber() &&
                    *tiles[y][col + 1].getInsideNumber() != 0 &&
                    !wereMerged)
                {
                    tiles[y][col + 1].replace(tiles[y][col].getPosition().x, tiles[y][col].getPosition().y);
                    tiles[y][col] = *(new Tile(tiles[y][col + 1]));
                    tiles[y][col].doubleTheNum();
                    tiles[y][col + 1] = *(new Tile(200 * y + 50, 200 * (col + 1) + 50, 0, emptyTileColor));
                    wereMerged = true;
                }
            }
        }
    }
}

void GameState::moveAllTilesDown()
{
    for (size_t y = 0; y < gridSize; y++)
    {
        bool wereMerged = false;
        for (size_t prevCol = gridSize - 2; prevCol != std::numeric_limits<size_t>::max(); prevCol--)
        {
            for (size_t col = gridSize - 1; col > 0; col--)
            {
                if (tiles[y][prevCol].getFillColor() != emptyTileColor && tiles[y][col].getFillColor() == emptyTileColor)
                {
                    tiles[y][prevCol].replace(tiles[y][col].getPosition().x, tiles[y][col].getPosition().y);
                    tiles[y][col] = *(new Tile(tiles[y][prevCol]));
                    tiles[y][prevCol] = *(new Tile(200 * y + 50, 200 * prevCol + 50, 0, emptyTileColor));
                }
                if (col < gridSize &&
                    *tiles[y][col - 1].getInsideNumber() == *tiles[y][col].getInsideNumber() &&
                    *tiles[y][col - 1].getInsideNumber() != 0 &&
                    !wereMerged)
                {
                    tiles[y][col - 1].replace(tiles[y][col].getPosition().x, tiles[y][col].getPosition().y);
                    tiles[y][col] = *(new Tile(tiles[y][col - 1]));
                    tiles[y][col].doubleTheNum();
                    tiles[y][col - 1] = *(new Tile(200 * y + 50, 200 * (col - 1) + 50, 0, emptyTileColor));
                    wereMerged = true;
                }
            }
        }
    }
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
    // for (size_t i = 0; i < pEmptyTiles.size(); i++)
    //     delete pEmptyTiles[i];

    // Т.к. pEmptyTils это массив указателей на элементы из tiles,
    // то чистить нам сами элементы не нужно, т.к. тогда
    // это произойдет повторно

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
                moveAllTilesRight();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                moveAllTilesLeft();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                moveAllTilesUp();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                moveAllTilesDown();

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