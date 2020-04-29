#include <functional>
#include <iostream>

#include "menu_view.h"
#include "game_view.h"
#include "../constants.h"
#include "../game.h"
#include "../resource_manager.h"

shooter::MenuView::MenuView(Game& game)
    : View("menu", game), m_optionIndex{0}
{
    m_options = {
        {
            L"Новая игра", [this]() {
            m_game.setView(std::make_unique<GameView>(m_game));
        }},
        {
            L"Настройки",  [this]() {
            std::cout << "Settings\n";
        }},
        {
            L"Выйти",      [this]() {
            m_game.window().close();
        }},
    };

    // TODO: pattern builder for sf::Text (+ director)
    // TODO: m_titleText = TextBuilder::defaultFont().setSize(60).setText(L"some text").build();
    // TODO: or
    // TODO: TextBuilder(m_titleText).setDefaultFont().setSize(60).setText(L"some text");
    m_titleText.setFont(ResourceManager::getDefaultFont());
    m_titleText.setCharacterSize(60);
    m_titleText.setFillColor(MAIN_COLOR);
    m_titleText.setString(L"Меню");
    sf::Vector2u windowSize = m_game.window().getSize();
    m_titleText.setPosition((windowSize.x - m_titleText.getLocalBounds().width) / 2,
        (windowSize.y - m_titleText.getLocalBounds().height) / 4);

    float y = static_cast<float>(windowSize.y) / 2;
    for (auto& option : m_options)
    {
        sf::Text text(option.first, ResourceManager::getDefaultFont(), 44);
        text.setFillColor(sf::Color::White);
        text.setPosition((windowSize.x - text.getLocalBounds().width) / 2, y);
        y += text.getLocalBounds().height + 40;
        m_choices.push_back(text);
    }
}

void shooter::MenuView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_titleText);
    for (auto& choice : m_choices)
    {
        target.draw(choice);
    }
}

void shooter::MenuView::update()
{
    for (auto& choice : m_choices)
    {
        choice.setFillColor(sf::Color::White);
    }
    m_choices[m_optionIndex].setFillColor(OPTION_SELECTED_COLOR);
}

void shooter::MenuView::processKey(const sf::Event::KeyEvent& key)
{
    switch (key.code)
    {
        case sf::Keyboard::Return:
            m_options[m_optionIndex].second();
            break;
        case sf::Keyboard::Down:
            m_optionIndex = std::min(m_optionIndex + 1, static_cast<int>(m_choices.size() - 1));
            break;
        case sf::Keyboard::Up:
            m_optionIndex = std::max(m_optionIndex - 1, 0);
            break;
        default:
            break;
    }
}
