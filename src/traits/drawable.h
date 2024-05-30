#pragma once
#include "trait.h"

class Drawable : public Trait
{
private:
    int draw_priority_ = 0;
public:
    Drawable(int draw_priority = 0);
    virtual ~Drawable();
    virtual void Draw() = 0;
    void SetDrawPriority(int priority) { draw_priority_ = priority; }
    int GetDrawPriority() const { return draw_priority_; }
};


