#ifndef SHOOTER_GAME_STATE_H
#define SHOOTER_GAME_STATE_H

#include <SFML/Graphics.hpp>
#include "util/timer.h"

namespace shooter
{
    class GameState
    {
    public:
        bool newGame;
        sf::Vector2f shipPos;
        std::vector<sf::RectangleShape> bullets;
        shooter::Timer shotTimer;

    public:
        GameState() : newGame{true}, shipPos{}, bullets{}, shotTimer{} {};

        void reset() { *this = GameState{}; }
    };
}

#endif //SHOOTER_GAME_STATE_H
