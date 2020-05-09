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

    sf::RectangleShape shot(sf::Vector2f const& pos)
    {
        sf::RectangleShape bullet{BULLET_SIZE};
        bullet.setFillColor(BULLET_COLOR);
        bullet.setPosition(pos);
        return bullet;
    }
}

shooter::GameView::GameView(Game& game)
    : View("game", game),
      m_ship(ResourcesManager::getTexture("ship.png"))
{
    m_ship.scale(0.5, 0.5);
    sf::FloatRect shipBbox = m_ship.getGlobalBounds();
    sf::Vector2u size = m_game.window().getSize();
    if (m_game.state().milliseconds() > 0)
    {
        m_ship.setPosition(m_game.state().shipPos);
    }
    else
    {
        m_ship.setPosition((size.x - shipBbox.width) / 2, size.y - shipBbox.height);
    }
    m_game.state().timer.start();
    m_game.state().shotTimer.start();
    m_game.state().bulletsTimer.start();
}

shooter::GameView::~GameView()
{
    m_game.state().timer.stop();
    m_game.state().shotTimer.stop();
    m_game.state().bulletsTimer.stop();
}

void shooter::GameView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_ship);
    for (auto& b : m_game.state().bullets)
    {
        target.draw(b);
    }
}

void shooter::GameView::update()
{
    sf::Vector2f const& pos = m_ship.getPosition();
    m_game.state().shipPos = pos;

    auto& bullets = m_game.state().bullets;

    // removing invisible bullets
    bullets.erase(std::remove_if(std::begin(bullets),
        std::end(bullets), [](sf::RectangleShape const& b) {
            return b.getPosition().y < -b.getSize().y;
        }), std::end(bullets));

    if (m_game.state().shotTimer.milliseconds() > 500)
    {
        bullets.push_back(shot({
            pos.x + m_ship.getGlobalBounds().width / 2 - BULLET_SIZE.x,
            pos.y - BULLET_SIZE.y
        }));
        m_game.state().shotTimer.reset();
    }

    if (m_game.state().bulletsTimer.milliseconds() > 10)
    {
        for (auto& b : bullets)
        {
            b.move(0, -5);
        }
        m_game.state().bulletsTimer.reset();
    }

    std::cout << m_game.state().milliseconds() << "\n";
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
