#ifndef SHOOTER_INPUT_CONTROLLER_H
#define SHOOTER_INPUT_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include "game.h"

namespace shooter
{
    enum class Movements
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    class InputController
    {
    private:
        sf::Window& m_window;
        shooter::Game& m_game;

    public:

        /**
         * @brief processor for all interactivity actions
         *
         * @param window
         * @param game shooter::Game& instance
         */
        explicit InputController(sf::Window& window, shooter::Game& game);

        void processEvent(sf::Event const& event);
    };
}


#endif //SHOOTER_INPUT_CONTROLLER_H
