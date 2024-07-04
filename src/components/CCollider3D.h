#pragma once
#include <vector>

#include "Component.h"
#include "transform.h"
#include "traits/physics3D.h"

class CCollider3D : public Component,public Physics3D
{
protected:
    Transform transform_ = Transform::Identity();
    bool dynamic_ = false;
    bool first_frame_ = true;
    std::vector<CCollider3D*> collided_;

public:
    CCollider3D() : Component("Collider3D") {};
    virtual ~CCollider3D() = default;
    virtual void UpdateCollision() = 0;
    virtual bool CheckCollision(CCollider3D* collider) = 0;
    virtual void ApplyCollision() = 0;
    std::vector<CCollider3D*> GetCollided(){return collided_;}
    void SetDynamic(bool dynamic){dynamic_ = dynamic;}
    Transform* GetTransform(){return &transform_;}
};
