#include "timerclass.h"


TimerClass::TimerClass()
{
}


TimerClass::TimerClass(const TimerClass& other)
{
}


TimerClass::~TimerClass()
{
}

bool TimerClass::Initialize()
{
    Logger::Get().Log("Initilazing timer class", __FILE__, __LINE__, Logger::LogLevel::Initialize);

    INT64 frequency;


    // Get the cycles per second speed for this system.
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
    if (frequency == 0)
    {
        Logger::Get().Log("QueryPerformanceFrequency failed", __FILE__, __LINE__, Logger::LogLevel::Error);
        return false;
    }

    // Store it in floating point.
    m_frequency = (float)frequency;

    // Get the initial start time.
    QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

    Logger::Get().Log("Timer class initialized", __FILE__, __LINE__, Logger::LogLevel::Initialize);

    return true;
}

void TimerClass::Frame()
{
    INT64 currentTime;
    INT64 elapsedTicks;


    // Query the current time.
    QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

    // Calculate the difference in time since the last time we queried for the current time.
    elapsedTicks = currentTime - m_startTime;

    // Calculate the frame time.
    m_frameTime = (float)elapsedTicks / m_frequency;

    // Restart the timer.
    m_startTime = currentTime;

    return;
}

float TimerClass::GetTime()
{
    return m_frameTime;
}
