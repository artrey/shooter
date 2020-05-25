#include <cmath>

#include "constants.h"
#include "fps.h"
#include "util/resources_manager.h"

shooter::FpsCounter::FpsCounter() : m_frames{0}
{
    m_fpsText.setFont(ResourcesManager::getDefaultFont());
    m_fpsText.setCharacterSize(16);
    m_fpsText.setFillColor(MAIN_COLOR);

    m_timer.restart();
}

void shooter::FpsCounter::update(sf::Time const& time)
{
    m_frames++;

    if (m_timer.getElapsedTime().asSeconds() > 0.2)
    {
        m_fpsText.setString(
            "FPS: " + std::to_string(static_cast<unsigned>(
                std::round(static_cast<float>(m_frames) /
                           m_timer.getElapsedTime().asSeconds()))));
        m_frames = 0;
        m_timer.restart();
    }
}

void shooter::FpsCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_fpsText);
}
