#pragma once
#include <DirectXMath.h>

#include "components/CCollider3D.h"
#include "manager.h"
#include "components/Component.h"

class CBulletBehaviour : public Component
{
private:
    DirectX::XMFLOAT3 start_pos_;

public:
    CBulletBehaviour() : Component("BulletBehaviour")
    {
    };
    ~CBulletBehaviour() override = default;

    void Start() override
    {
        start_pos_ = Manager::FindEntityByID(parent_id_)->GetTransform()->position;
    }

    void Update() override
    {
        //if bullet is too far from start position, remove it
        if (XMVectorGetX(XMVector3Length(XMVectorSubtract(
            XMLoadFloat3(&(Manager::FindEntityByID(parent_id_)->GetTransform()->position)),
            XMLoadFloat3(&start_pos_)))) > 30.0f||
            Manager::FindEntityByID(parent_id_)->GetComponent<CCollider3D>()->GetCollided().size() > 0)
        {
            Manager::QueueForRemoval(parent_id_);
        }
    }

    void CleanUp() override
    {
    }
};
