#pragma once
#include <DirectXMath.h>
#include "Component.h"
#include "manager.h"
#include "transform.h"

class CTransformConstraint : public Component
{
private:
    DirectX::XMFLOAT3 position_start_ = DirectX::XMFLOAT3(-100, 0, -100);
    DirectX::XMFLOAT3 position_end_ = DirectX::XMFLOAT3(100, 100, 100);
public:
    CTransformConstraint() : Component("TransformConstraint",PhysicsBehaviour)
    {
    }
    void Start() override{};
    void Update() override{
        //constrain position
        parent_entity_->Lock();
        Transform& transform = parent_entity_->GetTransform();
        if (transform.position.x < position_start_.x)
        {
            Transform::MoveTo(transform,DirectX::XMFLOAT3(position_start_.x, transform.position.y, transform.position.z));
        }
        if (transform.position.y < position_start_.y)
        {
            Transform::MoveTo(transform,DirectX::XMFLOAT3(transform.position.x, position_start_.y, transform.position.z));
        }
        if (transform.position.z < position_start_.z)
        {
            Transform::MoveTo(transform,DirectX::XMFLOAT3(transform.position.x, transform.position.y, position_start_.z));
        }

        if (transform.position.x > position_end_.x)
        {
            Transform::MoveTo(transform,DirectX::XMFLOAT3(position_end_.x, transform.position.y, transform.position.z));
        }
        if (transform.position.y > position_end_.y)
        {
            Transform::MoveTo(transform,DirectX::XMFLOAT3(transform.position.x, position_end_.y, transform.position.z));
        }

        if(transform.position.z > position_end_.z)
        {
            Transform::MoveTo(transform,DirectX::XMFLOAT3(transform.position.x, transform.position.y, position_end_.z));
        }
        parent_entity_->Unlock();
    }
    void CleanUp() override{};
    ~CTransformConstraint() override = default;


};
