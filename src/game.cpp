#include <utility>

#include "game.h"
#include "views/game_view.h"
#include "views/menu_view.h"

shooter::Game::Game()
    : m_state{}, m_currentView{new MenuView}, m_fpsCounter{}
{
}

void shooter::Game::update()
{
    m_currentView->update();
    m_fpsCounter.update();
}

void shooter::Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*m_currentView);
    target.draw(m_fpsCounter);
}

void shooter::Game::setView(std::unique_ptr<View> view)
{
    m_currentView = std::move(view);
}

void shooter::Game::nextScreen()
{
    m_currentView->nextScreen(*this);
}

shooter::GameState &shooter::Game::state()
{
    return m_state;
}
