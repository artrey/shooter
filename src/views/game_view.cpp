#include <cmath>
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

    template<typename T>
    double length(sf::Vector2<T> const& v)
    {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    template<typename T>
    sf::Vector2<T> normalize(sf::Vector2<T> const& v)
    {
        double len = length(v);
        if (std::abs(len) < EPSILON)
        {
            return {0, 0};
        }
        return v / static_cast<T>(len);
    }

    template<typename T>
    double distance(sf::Vector2<T> const& v1, sf::Vector2<T> const& v2)
    {
        return length(v1 - v2);
    }
}

shooter::GameView::GameView(Game& game)
    : View("game", game),
      m_ship(ResourcesManager::getTexture("ship.png")),
      m_horizontalShift{0}, m_verticalShift{0}
{
    m_ship.scale(0.5, 0.5);
    sf::FloatRect shipBbox = m_ship.getGlobalBounds();
    sf::Vector2u size = m_game.window().getSize();
    if (m_game.state().newGame)
    {
        m_ship.setPosition((size.x - shipBbox.width) / 2, size.y - shipBbox.height);
        m_game.state().newGame = false;
    }
    else
    {
        m_ship.setPosition(m_game.state().shipPos);
    }
    m_game.state().shotTimer.start();
}

shooter::GameView::~GameView()
{
    m_game.state().shotTimer.stop();
}

void shooter::GameView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_ship);
    for (auto& b : m_game.state().bullets)
    {
        target.draw(b);
    }
}

void shooter::GameView::update(sf::Time const& time)
{
    auto moveShip = [this](sf::Vector2f const& offset) {
        moveObject(m_ship, m_game.window().getSize(), offset);
    };

    auto& bullets = m_game.state().bullets;

    auto moveGameObjects = [this, &moveShip, &bullets](float timeOffset) {
        moveShip(SHIP_SPEED_PPS * timeOffset * normalize(
            sf::Vector2f(m_horizontalShift, m_verticalShift)));

        for (auto& b : bullets)
        {
            b.move(0, -BULLET_SPEED_PPS * timeOffset);
        }
    };

    float const safeTimeQuantum = 1 / SHIP_EMIT_BULLET_PER_SEC;
    float prevShot = m_game.state().shotTimer.seconds();
    float delta = time.asSeconds();
    while (delta > safeTimeQuantum - prevShot)
    {
        moveGameObjects(safeTimeQuantum - prevShot);

        sf::Vector2f const& pos = m_ship.getPosition();
        bullets.push_back(shot({
            pos.x + m_ship.getGlobalBounds().width / 2 - BULLET_SIZE.x,
            pos.y - BULLET_SIZE.y
        }));

        delta -= safeTimeQuantum - prevShot;
        prevShot = 0.f;
        m_game.state().shotTimer.reset();
    }

    moveGameObjects(delta);

    m_game.state().shipPos = m_ship.getPosition();

    // removing invisible bullets
    bullets.erase(std::remove_if(std::begin(bullets),
        std::end(bullets), [](sf::RectangleShape const& b) {
            return b.getPosition().y < -b.getSize().y;
        }), std::end(bullets));
}

void shooter::GameView::processKeyPressed(const sf::Event::KeyEvent& key)
{
    switch (key.code)
    {
        case sf::Keyboard::Escape:
            m_game.setView(std::make_unique<MenuView>(m_game));
            break;
        case sf::Keyboard::Down:
            m_verticalShift = 1;
            break;
        case sf::Keyboard::Up:
            m_verticalShift = -1;
            break;
        case sf::Keyboard::Left:
            m_horizontalShift = -1;
            break;
        case sf::Keyboard::Right:
            m_horizontalShift = 1;
            break;
        default:
            break;
    }
}

void shooter::GameView::processKeyReleased(const sf::Event::KeyEvent& key)
{
    switch (key.code)
    {
        case sf::Keyboard::Down:
        case sf::Keyboard::Up:
            m_verticalShift = 0;
            break;
        case sf::Keyboard::Left:
        case sf::Keyboard::Right:
            m_horizontalShift = 0;
            break;
        default:
            break;
    }
}
