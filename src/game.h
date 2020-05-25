#ifndef SHOOTER_GAME_H
#define SHOOTER_GAME_H

#include <memory>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "fps.h"
#include "game_state.h"
#include "views/view.h"
#include "util/timer.h"

namespace shooter
{
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

        void processKeyPressed(sf::Event::KeyEvent const& key);
        void processKeyReleased(sf::Event::KeyEvent const& key);

        void update(sf::Time const& time) override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void setView(std::unique_ptr<View> view);
    };
}

#endif
