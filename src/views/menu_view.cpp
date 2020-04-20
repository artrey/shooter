#include "../game.h"
#include "menu_view.h"
#include "game_view.h"

shooter::MenuView::MenuView()
    : View("menu")
{
}

void shooter::MenuView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
}

void shooter::MenuView::update()
{
}

void shooter::MenuView::nextScreen(shooter::Game &game)
{
    game.setView(std::make_unique<GameView>(game.state()));
}
