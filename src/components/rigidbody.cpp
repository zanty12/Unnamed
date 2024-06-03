#include "rigidbody.h"

#include "time.h"

void RigidBody::Update()
{
    float dt = Time::GetDeltaTime();
    linear_vel_.x += linear_accel_.x * dt;
    linear_vel_.y += linear_accel_.y * dt;
    linear_vel_.z += linear_accel_.z * dt;
    angular_vel_.x += angular_accel_.x * dt;
    angular_vel_.y += angular_accel_.y * dt;
    angular_vel_.z += angular_accel_.z * dt;
    linear_vel_.x += gravity_.x * dt;
    linear_vel_.y += gravity_.y * dt;
    linear_vel_.z += gravity_.z * dt;
}
