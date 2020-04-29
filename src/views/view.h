#ifndef SHOOTER_VIEW_H
#define SHOOTER_VIEW_H

#include <SFML/Graphics.hpp>

#include "../updateable.h"

namespace shooter
{
    class Game;

    class View : public sf::Drawable, public Updateable
    {
    protected:
        const std::string m_title;
        Game& m_game;

    public:
        View(std::string_view title, Game& game);

        ~View() override;

        virtual void processKey(sf::Event::KeyEvent const& key) = 0;

        [[nodiscard]] std::string title() const;
    };
}

#endif