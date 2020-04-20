#include "../game.h"
#include "game_view.h"
#include "menu_view.h"

shooter::GameView::GameView(shooter::GameState &state)
    : View("game"), m_state{state}
{
}

void shooter::GameView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
}

void shooter::GameView::update()
{
}

void shooter::GameView::nextScreen(shooter::Game &game)
{
    game.setView(std::make_unique<MenuView>());
}
