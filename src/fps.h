#ifndef SHOOTER_FPS_H
#define SHOOTER_FPS_H

#include "SFML/Graphics.hpp"
#include "updateable.h"

namespace shooter
{
    class FpsCounter : public sf::Drawable, public Updateable
    {
    public:
        FpsCounter();

        void update() override;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        sf::Text m_fpsText;
        sf::Clock m_timer;
        sf::Clock m_delayTimer;
        int m_frames;
    };
}

#endif //SHOOTER_FPS_H
