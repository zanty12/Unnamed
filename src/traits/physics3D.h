#pragma once
#include "trait.h"

class Physics3D : public Trait
{
public:
    Physics3D() : Trait("Physics3D") {};
    virtual ~Physics3D() = default;
};
