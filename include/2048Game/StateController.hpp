#pragma once
#include <2048Game/MenuState.hpp>
#include <2048Game/GameState.hpp>

class StateController
{
private:
    GameState *gs;
    MenuState *ms;
    sf::RenderWindow& window;
public:
    StateController(sf::RenderWindow& window);
    ~StateController();
    void initStateLoop();
};