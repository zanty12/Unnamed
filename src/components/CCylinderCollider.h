#pragma once
#include "CCollider3D.h"
#include "manager.h"
#include "physicssystem3D.h"

class CCylinderCollider : public CCollider3D
{
private:
    XMFLOAT3 center_offset_ = XMFLOAT3(0.0f, 0.0f, 0.0f);
    float radius_ = 1.0f;
    float height_ = 1.0f;

public:
    void Start() override
    {
        PhysicsSystem3D::AddCollider3D(this);
    }

    void Update() override
    {
        if (!dynamic_)
        {
            //move collider to parent
            //move collider to parent
            Transform::Copy(&this->transform_, Manager::FindEntityByID(parent_id_)->GetTransform());
            Transform::MoveBy(&this->transform_, center_offset_);
            collided_.clear();
            first_frame_ = false;
        }
    }

    void CleanUp() override
    {
        PhysicsSystem3D::RemoveCollider3D(this);
    }

    void SetCenterOffset(XMFLOAT3 center_offset) { center_offset_ = center_offset; }
    void SetRadius(float radius) { radius_ = radius; }

    void UpdateCollision() override
    {
        if (!dynamic_)
        {
            std::vector<Physics3D*> colliders = PhysicsSystem3D::GetPhysics3D();
            for (auto other : colliders)
            {
                CCollider3D* collider = dynamic_cast<CCollider3D*>(other);
                if (this->CheckCollision(collider))
                    collided_.push_back(collider);
            }
        }
    }

    bool CheckCollision(CCollider3D* collider) override
    {
        //check if the collider is a cylinder
        CCylinderCollider* cylinder_collider = dynamic_cast<CCylinderCollider*>(collider);
        if (cylinder_collider)
        {
            Transform* other_transform = collider->GetTransform();
            //check for radial
            XMFLOAT3 radial_delta = XMFLOAT3(transform_.position.x - other_transform->position.x,
                                             0,
                                             transform_.position.z - other_transform->position.z);
            float lengthsq = radial_delta.x * radial_delta.x + radial_delta.z * radial_delta.z;
            bool radial = lengthsq < (radius_ * this->transform_.scale.x + cylinder_collider->radius_ * other_transform
                ->scale.x) * (radius_ * this->transform_.scale.x + cylinder_collider->radius_ * other_transform->scale.
                x);
            //check for height
            float top = transform_.position.y + height_ * this->transform_.scale.y / 2.0f;
            float bottom = transform_.position.y - height_ * this->transform_.scale.y / 2.0f;
            float other_top = other_transform->position.y + cylinder_collider->height_ * other_transform->scale.y / 2.0f;
            float other_bottom = other_transform->position.y - cylinder_collider->height_ * other_transform->scale.y / 2.0f;
            bool height = (top > other_bottom && bottom < other_top) || (other_top > bottom && other_bottom < top);
            return radial && height;
        }
        return false;
    }
};
