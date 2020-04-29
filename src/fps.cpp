#include <cmath>

#include "fps.h"
#include "resource_manager.h"
#include "constants.h"

shooter::FpsCounter::FpsCounter() : m_frames{0}
{
    m_fpsText.setFont(ResourceManager::getDefaultFont());
    m_fpsText.setCharacterSize(16);
    m_fpsText.setFillColor(MAIN_COLOR);

    m_timer.restart();
}

void shooter::FpsCounter::update()
{
    m_frames++;

    if (m_delayTimer.getElapsedTime().asSeconds() > 0.2)
    {
        m_fpsText.setString(
                "FPS: " + std::to_string(static_cast<unsigned>(
                                                 std::round(static_cast<float>(m_frames) /
                                                            m_timer.getElapsedTime().asSeconds()))));
        m_frames = 0;
        m_timer.restart();
        m_delayTimer.restart();
    }
}

void shooter::FpsCounter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_fpsText);
}
