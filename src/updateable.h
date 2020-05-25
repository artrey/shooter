#ifndef SHOOTER_UPDATEABLE_H
#define SHOOTER_UPDATEABLE_H

#include <SFML/System/Time.hpp>

namespace shooter
{
    class Updateable
    {
    public:
        virtual void update(sf::Time const& time) = 0;
    };
}

#endif //SHOOTER_UPDATEABLE_H
