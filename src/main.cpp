#include <2048Game/StateController.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(850u, 850u), "2048", sf::Style::Close);
    window.setFramerateLimit(120);
    StateController sc(window);
    sc.initStateLoop();
    return 0;
}
