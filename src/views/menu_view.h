#ifndef SHOOTER_MENU_VIEW_H
#define SHOOTER_MENU_VIEW_H

#include "view.h"

namespace shooter
{
    class MenuView : public View
    {
    private:
        sf::Text m_text;

    public:
        explicit MenuView(Game& game);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void update() override;

        void processKey(sf::Event::KeyEvent const& key) override;
    };
}

#endif
