#pragma once
#include <2048Game/Hdrs.hpp>

class StateBase
{
private:
    void updateBaseEvents(sf::Event &event);
    bool stateAvailable;
public:
    sf::RenderWindow &window;
    StateBase(sf::RenderWindow &m_window);
    void initializeState();
    void saveState();
    void exitState();
    void setAvailable();
    bool init();
    void clear();
    virtual void updateEvents(sf::Event &event) = 0;
    virtual void update() = 0;

    /*  ///////////////////////////////////////
        ////////////////EXAMPLE////////////////
        ///////////////////////////////////////
    class GameState : public StateBase
    {
    private:
         float circleRadius = 50.f;
         sf::CircleShape cir;
    public:
        GameState(sf::RenderWindow& window)
        : StateBase(window)
        {
        }
        void init() override
        {
             cir.setRadius(circleRadius);
             cir.setFillColor(sf::Color::Red);
        }
        void updateEvents(sf::Event &event) override
        {
            //if (event.type == sf::Event::EventType)
            //     code
        }
        void update() override
        {
             window.clear();
            // code
        }
    };
        ///////////////////////////////////////
        //////////////EXAMPLE END//////////////
        ///////////////////////////////////////
    */
};
