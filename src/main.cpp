#include <SFML/Graphics.hpp>
#include "game.h"
#include "input_controller.h"

int main()
{
    const char *title = "Shooter";
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), title, sf::Style::None);
//    window.setFramerateLimit(60);

    shooter::Game game(window);
    shooter::InputController input(window, game);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            input.processEvent(event);
        }

        game.update();

        window.clear();
        window.draw(game);
        window.display();
    }

    return 0;
}
