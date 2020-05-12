#include "input_controller.h"

shooter::InputController::InputController(sf::Window& window, shooter::Game& game)
    : m_window{window}, m_game{game}
{
}

void shooter::InputController::processEvent(const sf::Event& event)
{
    if (event.type == sf::Event::Closed)
    {
        m_window.close();
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        // TODO: rename processKey to processKeyPressed
        m_game.processKey(event.key);
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        // TODO: call processKeyReleased on game
    }
}
