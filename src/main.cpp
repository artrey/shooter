#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>

int main()
{
    const char *title = "Shooter";
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), title, sf::Style::None);
    window.setFramerateLimit(60);

    shooter::Game game{};

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;

                    case sf::Keyboard::Return:
                        game.nextScreen();
                        break;

                    default:
                        break;
                }
            }
        }

        game.update();

        window.clear();
        window.draw(game);
        window.display();
    }

    return 0;
}
