#ifndef SHOOTER_GAME_VIEW_H
#define SHOOTER_GAME_VIEW_H

#include "view.h"

namespace shooter
{
    class GameView : public View
    {
    private:
        sf::Sprite m_ship;

    public:
        explicit GameView(Game& game);
        ~GameView() override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void update() override;

        void processKey(sf::Event::KeyEvent const& key) override;
    };
}

#endif
