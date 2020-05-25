#include "menu_view.h"
#include "game_view.h"
#include "../constants.h"
#include "../game.h"
#include "../util/text_builder.h"

shooter::MenuView::MenuView(Game& game)
    : View("menu", game), m_optionIndex{0}
{
    m_options = {
        {
            NEW_GAME_OPTION, [this]() {
            m_game.state().reset();
            m_game.setView(std::make_unique<GameView>(m_game));
        }},
        {
            EXIT_OPTION,     [this]() {
            m_game.window().close();
        }},
    };

    if (!m_game.state().newGame)
    {
        m_options.insert(std::begin(m_options), {
            RESUME_GAME_OPTION, [this]() {
                m_game.setView(std::make_unique<GameView>(m_game));
            }}
        );
    }

    m_titleText = TextBuilder::defaultParameters().setSize(60).setText(GAME_TITLE).build();
    sf::Vector2u windowSize = m_game.window().getSize();
    m_titleText.setPosition((windowSize.x - m_titleText.getGlobalBounds().width) / 2,
        (windowSize.y - m_titleText.getGlobalBounds().height) / 4);

    float y = static_cast<float>(windowSize.y) / 2;
    for (auto& option : m_options)
    {
        sf::Text text = TextBuilder::defaultParameters().setSize(44).setText(option.first).build();
        text.setPosition((windowSize.x - text.getGlobalBounds().width) / 2, y);
        y += text.getGlobalBounds().height + 40;
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

void shooter::MenuView::update(sf::Time const& time)
{
    for (auto& choice : m_choices)
    {
        choice.setFillColor(sf::Color::White);
    }
    m_choices[m_optionIndex].setFillColor(OPTION_SELECTED_COLOR);
}

void shooter::MenuView::processKeyPressed(const sf::Event::KeyEvent& key)
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

void shooter::MenuView::processKeyReleased(const sf::Event::KeyEvent& key)
{
}
