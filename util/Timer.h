#pragma once

#include <chrono>
#include <iostream>

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
    std::chrono::duration<double> m_Duration;
public:
    Timer()
    {
        m_StartTime = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
        m_Duration = end - m_StartTime;
        double ms = m_Duration.count() * 1000.0;
        std::cout << "(" << ms << " ms) ";
    }
};
