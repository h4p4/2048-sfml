#include <2048Game/StateBase.hpp>

StateBase::StateBase(sf::RenderWindow &m_window) : window(m_window),
                                                   stateAvailable(true)
{
}

void StateBase::updateBaseEvents(sf::Event &event)
{
    if (event.type == sf::Event::Closed)
        window.close();
    if (event.type == sf::Event::Resized)
    {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
    }
}
void StateBase::initializeState()
{
    while (window.isOpen() && stateAvailable)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            updateBaseEvents(event);
            updateEvents(event);
        }
        update();
        window.display();
    }
    stateAvailable = true;
}
void StateBase::exitState()
{
    stateAvailable = false;
}
