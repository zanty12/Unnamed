#pragma once
#include <DirectXMath.h>

#include "CCollider3D.h"
#include "manager.h"
#include "Component.h"

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
        start_pos_ = Manager::FindEntity(parent_id_)->GetTransform()->position;
    }

    void Update() override
    {
        //if bullet is too far from start position, remove it
        if (XMVectorGetX(XMVector3Length(XMVectorSubtract(
            XMLoadFloat3(&(Manager::FindEntity(parent_id_)->GetTransform()->position)),
            XMLoadFloat3(&start_pos_)))) > 20.0f||
            Manager::FindEntity(parent_id_)->GetComponent<CCollider3D>()->GetCollided().size() > 0)
        {
            Manager::QueueForRemoval(parent_id_);
        }
    }

    void CleanUp() override
    {
    }
};
