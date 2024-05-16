#pragma once

class Drawable
{
public:
    Drawable();
    virtual ~Drawable() = default;
    virtual void Draw() = 0;
};


