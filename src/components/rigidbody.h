#pragma once
#include "main.h"
#include "component.h"

class RigidBody : public Component
{
private:
    XMFLOAT3 linear_vel_;
    XMFLOAT3 angular_vel_;
    XMFLOAT3 gravity_;

    float mass = 1;
public:
    RigidBody() : Component("RigidBody")
    {
        linear_vel_ = XMFLOAT3(0, 0, 0);
        angular_vel_ = XMFLOAT3(0, 0, 0);
        gravity_ = XMFLOAT3(0, -9.8f, 0);
    }
    ~RigidBody() override = default;
    void Start() override{};
    void Update() override;
    void CleanUp() override{};

    void LinearAccel(XMFLOAT3 accel)
    {
        linear_vel_.x += accel.x;
        linear_vel_.y += accel.y;
        linear_vel_.z += accel.z;
    }

    void AngularAccel(XMFLOAT3 accel)
    {
        angular_vel_.x += accel.x;
        angular_vel_.y += accel.y;
        angular_vel_.z += accel.z;
    }


    void SetLinearVel(XMFLOAT3 vel)
    {
        linear_vel_ = vel;
    }

    void SetAngularVel(XMFLOAT3 vel)
    {
        angular_vel_ = vel;
    }

    void SetGravity(XMFLOAT3 gravity)
    {
        gravity_ = gravity;
    }

    void SetMass(float m)
    {
        mass = m;
    }

    XMFLOAT3 GetLinearVel()
    {
        return linear_vel_;
    }

    XMFLOAT3 GetAngularVel()
    {
        return angular_vel_;
    }

    XMFLOAT3 GetGravity()
    {
        return gravity_;
    }

    float GetMass()
    {
        return mass;
    }


};
