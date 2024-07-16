#pragma once
#include "CCollider3D.h"
#include "manager.h"
#include "system/physicssystem3D.h"

class CSphereCollider : public CCollider3D
{
private:
    XMFLOAT3 center_offset_ = XMFLOAT3(0.0f, 0.0f, 0.0f);
    float radius_ = 1.0f;

public:
    void Start() override
    {
        PhysicsSystem3D::AddCollider3D(this);
    }

    void Update() override
    {
        if (dynamic_ || first_frame_)
        {
            //move collider to parent
            Transform::Copy(&this->transform_, Manager::FindEntity(parent_id_)->GetTransform());
            Transform::MoveBy(&this->transform_, center_offset_);
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
        collided_.clear();
        std::vector<Physics3D*> colliders = PhysicsSystem3D::GetPhysics3D();
        for (auto other : colliders)
        {
            CCollider3D* collider = dynamic_cast<CCollider3D*>(other);
            if (this->CheckCollision(collider))
                collided_.push_back(collider);
        }
    }

    bool CheckCollision(CCollider3D* collider) override
    {
        //check if the collider is a sphere
        CSphereCollider* sphere_collider = dynamic_cast<CSphereCollider*>(collider);
        if (sphere_collider)
        {
            if (sphere_collider == this)
                return false;
            //check if the distance between the two centers is less than the sum of the radii
            XMFLOAT3 distance = XMFLOAT3(transform_.position.x - collider->GetTransform()->position.x,
                                         transform_.position.y - collider->GetTransform()->position.y,
                                         transform_.position.z - collider->GetTransform()->position.z);
            float distance_length = (distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
            if (distance_length < (radius_ + sphere_collider->radius_) * (radius_ + sphere_collider->radius_))
                return true;
            return false;
        }
        return false;
    }

    void ApplyCollision() override
    {
        if(dynamic_)
        {
            for (auto other : collided_)
            {
                //check if the collider is a sphere
                CSphereCollider* sphere_collider = dynamic_cast<CSphereCollider*>(other);
                if (sphere_collider)
                {
                    //check if the distance between the two centers is less than the sum of the radii
                    XMFLOAT3 distance = XMFLOAT3(transform_.position.x - other->GetTransform()->position.x,
                                                 transform_.position.y - other->GetTransform()->position.y,
                                                 transform_.position.z - other->GetTransform()->position.z);
                    float distance_length = sqrt(
                        distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
                    float overlap = (radius_ + sphere_collider->radius_) - distance_length;
                    XMFLOAT3 direction = XMFLOAT3(distance.x / distance_length, distance.y / distance_length,
                                                  distance.z / distance_length);
                    XMFLOAT3 correction = XMFLOAT3(direction.x * overlap, direction.y * overlap, direction.z * overlap);
                    Transform::MoveBy(&transform_, correction);
                    Transform::Copy(&transform_, Manager::FindEntity(parent_id_)->GetTransform());
                }
            }
        }
    }
};
