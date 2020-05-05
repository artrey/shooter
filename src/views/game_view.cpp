#include <iostream>
#include "game_view.h"
#include "menu_view.h"
#include "../constants.h"
#include "../game.h"
#include "../util/resources_manager.h"

namespace shooter
{
    sf::Vector2f findPointPos(sf::Transformable const& obj, sf::Vector2f const& bbox, sf::Vector2f const& offset)
    {
        sf::Vector2f pos = obj.getPosition() + offset;
        pos.x = std::max(0.f, std::min(pos.x, bbox.x));
        pos.y = std::max(0.f, std::min(pos.y, bbox.y));
        return pos;
    }

    template<typename T>
    sf::Vector2f findObjectPos(T const& obj, sf::Vector2u const& bbox, sf::Vector2f const& offset)
    {
        sf::FloatRect objBbox = obj.getGlobalBounds();
        return findPointPos(obj, sf::Vector2f(bbox.x - objBbox.width, bbox.y - objBbox.height), offset);
    }

    template<typename T>
    void moveObject(T& obj, sf::Vector2u const& bbox, sf::Vector2f const& offset)
    {
        obj.setPosition(findObjectPos(obj, bbox, offset));
    }
}

shooter::GameView::GameView(Game& game)
    : View("game", game),
      m_ship(ResourcesManager::getTexture("ship.png"))
{
    m_ship.scale(0.5, 0.5);
    sf::FloatRect shipBbox = m_ship.getGlobalBounds();
    sf::Vector2u size = m_game.window().getSize();
    m_ship.setPosition((size.x - shipBbox.width) / 2, size.y - shipBbox.height);
}

void shooter::GameView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_ship);
}

void shooter::GameView::update()
{
    std::cout << m_game.state().incTime() << "\n";
}

void shooter::GameView::processKey(const sf::Event::KeyEvent& key)
{
    auto moveShip = [this](sf::Vector2f const& offset) {
        moveObject(m_ship, m_game.window().getSize(), offset);
    };

    switch (key.code)
    {
        case sf::Keyboard::Escape:
            m_game.setView(std::make_unique<MenuView>(m_game));
            break;
        case sf::Keyboard::Down:
            moveShip(sf::Vector2f(0, SHIFT_POS));
            break;
        case sf::Keyboard::Up:
            moveShip(sf::Vector2f(0, -SHIFT_POS));
            break;
        case sf::Keyboard::Left:
            moveShip(sf::Vector2f(-SHIFT_POS, 0));
            break;
        case sf::Keyboard::Right:
            moveShip(sf::Vector2f(SHIFT_POS, 0));
            break;
        default:
            break;
    }
}
