#pragma once

class GameMode
{
public:
    GameMode() = default;
    virtual ~GameMode() = default;
    virtual void Update() =0;
};
