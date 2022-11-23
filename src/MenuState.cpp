#include <2048Game/MenuState.hpp>


MenuState::MenuState(sf::RenderWindow &window, GameState &gs) : StateBase(window), gs(gs) {}
MenuState::~MenuState()
{
    clear();
}

bool MenuState::init()
{
    return true;
}

void MenuState::clear()
{
    // code
}

void MenuState::updateEvents(sf::Event &event)
{
    if (event.type == sf::Event::EventType::KeyPressed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            this->exitState(); // -- ВЫХОД ИЗ СОСТОЯНИЯ --
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
        {
            gs.clear();
            gs.init();
        }
    }
}

void MenuState::update()
{
    window.clear(sf::Color::White);
    // code
}