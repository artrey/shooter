#include <iostream>
#include "../game.h"
#include "menu_view.h"
#include "game_view.h"
#include "../resource_manager.h"

shooter::MenuView::MenuView(Game &game)
        : View("menu", game)
{
    m_text.setFont(ResourceManager::getDefaultFont());
    m_text.setCharacterSize(30);
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineThickness(3);
    m_text.setString(title());
}

void shooter::MenuView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_text);
}

void shooter::MenuView::update()
{
    sf::Vector2u windowSize = m_game.window().getSize();
    m_text.setPosition((windowSize.x - m_text.getLocalBounds().width) / 2,
                       (windowSize.y - m_text.getLocalBounds().height) / 2);
}

void shooter::MenuView::processKey(const sf::Event::KeyEvent &key)
{
    switch (key.code)
    {
        case sf::Keyboard::Escape:
            std::cout << "Escape from menu\n";
            break;
        case sf::Keyboard::Return:
            m_game.setView(std::make_unique<GameView>(m_game));
            break;
        default:
            std::cout << "Pressed unsupported key in menu: " << key.code << std::endl;
            break;
    }
}
