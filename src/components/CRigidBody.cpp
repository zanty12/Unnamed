#include "CRigidBody.h"

#include "manager.h"
#include "system/timesystem.h"
#include "transform.h"

void CRigidBody::Update()
{
    float dt = Time::GetDeltaTime();

    //linear
    //acceleration(account for drag)
    if (use_drag_)
    {
        XMFLOAT3 linear_dir = linear_vel_;
        XMStoreFloat3(&linear_dir, XMVector3Normalize(XMLoadFloat3(&linear_dir)));
        XMFLOAT3 linear_drag = linear_dir;
        linear_drag.x *= -linear_drag_;
        linear_drag.y *= -linear_drag_;
        linear_drag.z *= -linear_drag_;
        linear_accel_.x += linear_drag.x;
        linear_accel_.y += linear_drag.y;
        linear_accel_.z += linear_drag.z;
    }
    //apply gravity
    if (use_gravity_)
    {
        linear_vel_.x += gravity_.x * dt;
        linear_vel_.y += gravity_.y * dt;
        linear_vel_.z += gravity_.z * dt;
    }
    //apply acceleration
    linear_vel_.x += linear_accel_.x * dt;
    linear_vel_.y += linear_accel_.y * dt;
    linear_vel_.z += linear_accel_.z * dt;
    //apply constraints
    if (constrain_linear_x_)
    {
        linear_vel_.x = 0;
    }
    if (constrain_linear_y_)
    {
        linear_vel_.y = 0;
    }
    if (constrain_linear_z_)
    {
        linear_vel_.z = 0;
    }

    //angular
    //acceleration(account for drag)
    if(use_angular_drag_)
    {
        XMFLOAT3 angular_dir = angular_vel_;
        XMStoreFloat3(&angular_dir, XMVector3Normalize(XMLoadFloat3(&angular_dir)));
        XMFLOAT3 angular_drag = angular_dir;
        angular_drag.x *= -angular_drag_;
        angular_drag.y *= -angular_drag_;
        angular_drag.z *= -angular_drag_;
        angular_accel_.x += angular_drag.x;
        angular_accel_.y += angular_drag.y;
        angular_accel_.z += angular_drag.z;
    }
    //apply acceleration
    angular_vel_.x += angular_accel_.x * dt;
    angular_vel_.y += angular_accel_.y * dt;
    angular_vel_.z += angular_accel_.z * dt;
    //apply constraints
    if (constrain_angular_x_)
    {
        angular_vel_.x = 0;
    }
    if (constrain_angular_y_)
    {
        angular_vel_.y = 0;
    }
    if (constrain_angular_z_)
    {
        angular_vel_.z = 0;
    }

    if(parent_id_ > -1)
    {
        //get parent transform
        Entity* parent = Manager::FindEntity(parent_id_);
        parent->Lock();
        Transform* parent_transform = parent->GetTransform();
        //apply linear velocity
        Transform::MoveBy(parent_transform, XMFLOAT3(linear_vel_.x * dt, linear_vel_.y * dt, linear_vel_.z * dt));
        //apply angular velocity
        Transform::RotateBy(parent_transform, XMFLOAT3(angular_vel_.x * dt, angular_vel_.y * dt, angular_vel_.z * dt));
        parent->Unlock();
    }
}
