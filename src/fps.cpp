#include <iostream>
#include <cmath>

#include "fps.h"

shooter::FpsCounter::FpsCounter() : m_fps{0}, m_frames{0}
{
    if (!m_font.loadFromFile("Cousine-Regular.ttf"))
    {
        std::cout << "Font not loaded!\n";
    }
    m_fpsText.setFont(m_font);
    m_fpsText.setCharacterSize(16);
    m_fpsText.setFillColor(sf::Color::White);
    m_fpsText.setOutlineThickness(2);

    m_timer.restart();
}

void shooter::FpsCounter::update()
{
    std::string fps = std::to_string(static_cast<unsigned int>(
                                             std::round(++m_frames / m_timer.getElapsedTime().asSeconds())));
    if (m_frames > 1000)
    {
        m_frames = 0;
        m_timer.restart();
    }
    m_fpsText.setString("FPS: " + fps);
}

void shooter::FpsCounter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_fpsText);
}
