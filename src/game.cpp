#include <utility>

#include "game.h"
#include "views/game_view.h"
#include "views/menu_view.h"


shooter::Game::Game(sf::Window &window)
    : m_window{window}, m_state{}, m_currentView{new MenuView(*this)}, m_fpsCounter{}
{
}

void shooter::Game::update(sf::Time const& time)
{
    m_currentView->update(time);
    m_fpsCounter.update(time);
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

sf::Window &shooter::Game::window()
{
    return m_window;
}

shooter::GameState &shooter::Game::state()
{
    return m_state;
}

void shooter::Game::processKeyPressed(const sf::Event::KeyEvent &key)
{
    m_currentView->processKeyPressed(key);
}

void shooter::Game::processKeyReleased(const sf::Event::KeyEvent& key)
{
    m_currentView->processKeyReleased(key);
}
