#pragma once
#include <vector>

#include "components/Component.h"
#include "components/transform.h"
#include "traits/physics3D.h"

class CCollider3D : public Component,public Physics3D
{
protected:
    bool dynamic_ = false;
    bool first_frame_ = true;
    std::vector<CCollider3D*> collided_;

public:
    CCollider3D() : Component("Collider3D",Kinematic) {};
    virtual ~CCollider3D() = default;
    virtual void UpdateCollision() = 0;
    virtual bool CheckCollision(CCollider3D* collider) = 0;
    virtual void ApplyCollision() = 0;
    std::vector<CCollider3D*> GetCollided(){return collided_;}
    void SetDynamic(bool dynamic){dynamic_ = dynamic;}
};
