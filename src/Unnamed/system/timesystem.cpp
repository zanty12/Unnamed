#include "timesystem.h"

#include <ios>
DWORD Time::startTime = 0;
DWORD Time::previousTime = 0;
DWORD Time::currentTime = 0;
DWORD Time::deltaTime = 0;
DWORD Time::fixedTime = 0;
bool Time::fixed_update = false;


void Time::Start(void)
{
    timeBeginPeriod(1000);
    startTime = currentTime = previousTime = timeGetTime();
}

void Time::CleanUp(void)
{
    startTime = timeGetTime();
    timeBeginPeriod(1000);
}

void Time::Update(void)
{
    previousTime = currentTime;
    currentTime = timeGetTime();
    deltaTime = currentTime - previousTime;
    fixedTime += deltaTime;
    if(fixedTime >= 16)
    {
        fixedTime = 0;
        fixed_update = true;
    }
    else
    {
        fixed_update = false;
    }
}

float Time::GetDeltaTime(void)
{
    return deltaTime * 0.001f;
}

float Time::GetDeltaTime(float start)
{
    return currentTime * 0.001f - start;
}

float Time::GetCurrentTime(void)
{
    return currentTime * 0.001f;
}

bool Time::FixedUpdate()
{
    return fixed_update;
}

