#include "timer.h"

shooter::Timer::Timer(const shooter::Timer::millis& initialTime)
    : m_time{initialTime}, m_timerHelper{}, m_started{false}
{
}

void shooter::Timer::start()
{
    m_started = true;
    m_timerHelper.restart();
}

void shooter::Timer::stop()
{
    m_time = time();
    m_started = false;
}

void shooter::Timer::reset()
{
    m_time = 0ms;
    m_timerHelper.restart();
}

shooter::Timer::millis shooter::Timer::time() const
{
    return m_time + std::chrono::milliseconds(m_started ? m_timerHelper.getElapsedTime().asMilliseconds() : 0);
}

std::int64_t shooter::Timer::milliseconds() const
{
    return time().count();
}

float shooter::Timer::seconds() const
{
    return milliseconds() / 1000.f;
}
