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

    public:
        explicit View(std::string title);
        ~View() override;

        virtual void nextScreen(Game& game) = 0;

        [[nodiscard]] std::string title() const;
    };
}

#endif