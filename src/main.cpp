#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "game.h"
#include "input_controller.h"
#include "util/resources_manager.h"

int main()
{
    try
    {
        shooter::ResourcesManager::init(RESOURCES_DIR);

        sf::RenderWindow window(sf::VideoMode::getDesktopMode(), GAME_TITLE, sf::Style::Default);
        window.setFramerateLimit(60);

        shooter::Game game(window);
        shooter::InputController input(window, game);

        sf::Clock globalTimer;

        while (window.isOpen())
        {
            sf::Event event{};
            while (window.pollEvent(event))
            {
                input.processEvent(event);
            }

            game.update(globalTimer.restart());

            window.clear();
            window.draw(game);
            window.display();
        }
    }
    catch (std::exception const& ex)
    {
        std::cout << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
