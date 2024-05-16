#pragma once
#include "trait.h"

class Drawable : public Trait
{
public:
    Drawable();
    virtual ~Drawable() = default;
    virtual void Draw() = 0;
};


