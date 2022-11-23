#include <2048Game/StateController.hpp>

StateController::StateController(sf::RenderWindow &window) : window(window)
{
}
StateController::~StateController()
{
    delete gs;
    delete ms;
} 
void StateController::initStateLoop()
{
    gs = new GameState(window);
    ms = new MenuState(window, *gs);
    while (window.isOpen())
    {
        // Т.к. в каждом из состояний реализован выход по клавише Esc,
        // то данные состояния будут поочередно между собой переключаться
        // по клавише Esc
        ms->initializeState();
        gs->initializeState();
    }
}