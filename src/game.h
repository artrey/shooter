#ifndef SHOOTER_GAME_H
#define SHOOTER_GAME_H

#include <memory>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "views/view.h"
#include "fps.h"

namespace shooter
{
    class GameState
    {
    private:
        std::uint64_t m_time;

    public:
        GameState() : m_time{0} {};

        [[nodiscard]] std::uint64_t time() const { return m_time; }

        std::uint64_t incTime() { return ++m_time; }

        void reset() { m_time = 0; }
    };

    class Game : public sf::Drawable, public Updateable
    {
    private:
        sf::Window& m_window;
        GameState m_state;
        std::unique_ptr<View> m_currentView;
        FpsCounter m_fpsCounter;

    public:
        explicit Game(sf::Window& window);

        sf::Window& window();

        GameState& state();

        void processKey(sf::Event::KeyEvent const& key);

        void update() override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void setView(std::unique_ptr<View> view);
    };
}

#endif
