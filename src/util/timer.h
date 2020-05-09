#ifndef SHOOTER_TIMER_H
#define SHOOTER_TIMER_H

#include <chrono>
#include <SFML/System/Clock.hpp>

namespace shooter
{
    using namespace std::chrono_literals;

    class Timer
    {
    public:
        using millis = std::chrono::milliseconds;

        explicit Timer(millis const& initialTime = 0ms);

        void start();
        void stop();
        void reset();

        [[nodiscard]] millis time() const;
        [[nodiscard]] std::int64_t milliseconds() const;

    private:
        millis m_time;
        sf::Clock m_timerHelper;
        bool m_started;
    };
}

#endif //SHOOTER_TIMER_H
