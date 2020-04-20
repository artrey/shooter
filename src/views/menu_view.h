#ifndef SHOOTER_MENU_VIEW_H
#define SHOOTER_MENU_VIEW_H

#include "view.h"

namespace shooter
{
    class MenuView : public View
    {
    public:
        MenuView();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void update() override;

        void nextScreen(Game& game) override;
    };
}

#endif
