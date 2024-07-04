#pragma once
#include "Component.h"
#include "transform.h"

class CCollider2D : public Component
{
protected:
    Transform transform_ = Transform::Identity();
    bool dynamic_ = false;
    bool collision_checked_ = false;
public:
    CCollider2D() : Component("CCollider2D") {};
    virtual ~CCollider2D() = default;
};
