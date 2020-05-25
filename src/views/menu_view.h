#ifndef SHOOTER_MENU_VIEW_H
#define SHOOTER_MENU_VIEW_H

#include <functional>

#include "view.h"

namespace shooter
{
    class MenuView : public View
    {
    private:
        sf::Text m_titleText;
        std::vector<sf::Text> m_choices;
        std::vector<std::pair<std::wstring, std::function<void()>>> m_options;
        int m_optionIndex;

    public:
        explicit MenuView(Game &game);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void update(sf::Time const& time) override;

        void processKeyPressed(sf::Event::KeyEvent const &key) override;
        void processKeyReleased(sf::Event::KeyEvent const &key) override;
    };
}

#endif
