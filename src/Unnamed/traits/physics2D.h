#pragma once
#include "trait.h"

class Physics2D : public  Trait
{
public:
    Physics2D() : Trait("Physics2D") {};
    virtual ~Physics2D() = default;
};
