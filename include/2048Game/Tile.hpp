#pragma once
#include <2048Game/Hdrs.hpp>


class Tile : public sf::RectangleShape
{
private:
    float tileWidth, textOffsetX;
    size_t insideNumber;
    sf::Text insideNumberText;
    void replaceText();
public:
    static sf::Font textFont;
    static bool loadFont();
    Tile(float x, float y, size_t insideNumber, sf::Color color);
    // ~Tile();
    void setInsideNumberText();
    void setInsideNumber(size_t insideNumber);
    void setTextColor(sf::Color color);
    sf::Text* getInsideNumberText();
    size_t* getInsideNumber();
    void replace(float x, float y);
    void doubleTheNum();
    bool isEmpty();
};


