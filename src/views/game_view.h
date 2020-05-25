#ifndef SHOOTER_GAME_VIEW_H
#define SHOOTER_GAME_VIEW_H

#include "view.h"

namespace shooter
{
    class GameView : public View
    {
    private:
        sf::Sprite m_ship;
        int8_t m_horizontalShift;
        int8_t m_verticalShift;

    public:
        explicit GameView(Game& game);
        ~GameView() override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void update(sf::Time const& time) override;

        void processKeyPressed(sf::Event::KeyEvent const& key) override;
        void processKeyReleased(sf::Event::KeyEvent const& key) override;
    };
}

#endif
