#pragma once
#include "main.h"
#include "component.h"

class RigidBody : public Component
{
private:
    XMFLOAT3 linear_vel_;
    XMFLOAT3 angular_vel_;
    XMFLOAT3 gravity_;
    XMFLOAT3 linear_accel_;
    XMFLOAT3 angular_accel_;

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

    void SetLinearVel(XMFLOAT3 vel)
    {
        linear_vel_ = vel;
    }

    void SetAngularVel(XMFLOAT3 vel)
    {
        angular_vel_ = vel;
    }

    void SetLinearAccel(XMFLOAT3 accel)
    {
        linear_accel_ = accel;
    }

    void SetAngularAccel(XMFLOAT3 accel)
    {
        angular_accel_ = accel;
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

    XMFLOAT3 GetLinearAccel()
    {
        return linear_accel_;
    }

    XMFLOAT3 GetAngularAccel()
    {
        return angular_accel_;
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
