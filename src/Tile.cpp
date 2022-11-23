#include <2048Game/Tile.hpp>

Tile::Tile(float x, float y, size_t insideNumber, sf::Color color)
{
    this->setFillColor(color);
    this->setPosition(x, y);
    this->tileWidth = 150.f;
    this->setSize(sf::Vector2f(tileWidth, tileWidth));
    this->insideNumber = insideNumber;
    this->setInsideNumberText();
}

sf::Font Tile::textFont;

bool Tile::loadFont()
{
    return Tile::textFont.loadFromFile("../resources/arial.ttf");
}


// Tile::~Tile()
// {
// }
sf::Text *Tile::getInsideNumberText()
{
    return &this->insideNumberText;
}
size_t* Tile::getInsideNumber()
{
    return &this->insideNumber;
}
void Tile::setInsideNumber(size_t insideNumber)
{
    this->insideNumber = insideNumber;
    this->setInsideNumberText();
}


void Tile::setInsideNumberText()
{
    sf::Text text(std::to_string(this->insideNumber), this->textFont);
    this->insideNumberText = text;
    this->insideNumberText.setFillColor(sf::Color(119, 110, 101));
    this->insideNumberText.setCharacterSize((int) this->tileWidth/2.3);
    this->insideNumberText.setStyle(sf::Text::Bold);
    this->textOffsetX = (insideNumberText.getCharacterSize()/5) * (1.4 * (std::to_string(this->insideNumber).length() - 1));

    this->replaceText();
}

void Tile::replaceText()
{
    this->insideNumberText.setPosition((this->getPosition().x + (this->getSize().x / 2.8) - textOffsetX), this->getPosition().y+(this->getSize().y / 5.3));
}

void Tile::replace(float x, float y)
{
    this->setPosition(x, y);
    this->replaceText();
}

void Tile::doubleTheNum()
{
    this->insideNumber *= 2;
    this->setInsideNumberText();
}

bool Tile::isEmpty()
{
    return this->insideNumber == 0;
}





