#include <iostream>
#include "game_view.h"
#include "menu_view.h"
#include "../game.h"

shooter::GameView::GameView(Game& game)
    : View("game", game)
{
}

void shooter::GameView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
}

void shooter::GameView::update()
{
}

void shooter::GameView::processKey(const sf::Event::KeyEvent &key)
{
    if (key.code == sf::Keyboard::Escape)
    {
        m_game.setView(std::make_unique<MenuView>(m_game));
    }
    else
    {
        std::cout << "Pressed unsupported key in game: " << key.code << std::endl;
    }
}
