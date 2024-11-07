#pragma once
#include <DirectXMath.h>

#include "components/depreciated/CCollider3D.h"
#include "manager.h"
#include "components/Component.h"

class CBulletBehaviour : public Component
{
private:
    DirectX::XMFLOAT3 start_pos_;

public:
    CBulletBehaviour() : Component("BulletBehaviour",PhysicsBehaviour)
    {
    };
    ~CBulletBehaviour() override = default;

    void Start() override
    {
        start_pos_ = Manager::FindEntityByID(parent_id_)->GetTransform().position;
    }

    void Update() override
    {
        //if bullet is too far from start position, remove it
        if (XMVectorGetX(XMVector3Length(XMVectorSubtract(
            XMLoadFloat3(&(Manager::FindEntityByID(parent_id_)->GetTransform().position)),
            XMLoadFloat3(&start_pos_)))) > 30.0f)
        {
            Manager::QueueForRemoval(parent_id_);
        }
    }

    void CleanUp() override
    {
    }
};
