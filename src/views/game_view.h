#ifndef SHOOTER_GAME_VIEW_H
#define SHOOTER_GAME_VIEW_H

#include "view.h"

namespace shooter
{
    class GameView : public View
    {
    private:
        GameState& m_state;

    public:
        explicit GameView(GameState& state);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void update() override;

        void nextScreen(Game& game) override;
    };
}

#endif
