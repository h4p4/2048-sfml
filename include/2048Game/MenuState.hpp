#pragma once
#include <2048Game/StateBase.hpp>
#include <2048Game/GameState.hpp>

class MenuState : public StateBase 
{
// private:
public:
    MenuState(sf::RenderWindow &window, GameState &gs);
    ~MenuState();
    GameState &gs;
    void updateEvents(sf::Event &event);
    void update();
    bool init();
    void clear();
};


