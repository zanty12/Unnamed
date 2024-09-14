#pragma once
#include "main.h"
#include "components/component.h"
#include "processpriority.h"
#include "traits/unique.h"

class CRigidBody : public Component, public Unique
{
private:
    XMFLOAT3 linear_vel_ = XMFLOAT3(0, 0, 0);
    XMFLOAT3 angular_vel_ = XMFLOAT3(0, 0, 0);
    XMFLOAT3 gravity_ = XMFLOAT3(0, -9.8f, 0);
    XMFLOAT3 linear_accel_ = XMFLOAT3(0, 0, 0);
    XMFLOAT3 angular_accel_ = XMFLOAT3(0, 0, 0);
    float linear_drag_ = 0.0f;
    float angular_drag_ = 0.0f;
    float mass = 1.0f;
    bool use_gravity_ = true;
    bool use_drag_ = true;
    bool use_angular_drag_ = true;
    bool constrain_linear_x_ = false;
    bool constrain_linear_y_ = false;
    bool constrain_linear_z_ = false;
    bool constrain_angular_x_ = false;
    bool constrain_angular_y_ = false;
    bool constrain_angular_z_ = false;

public:
    CRigidBody() : Component("RigidBody",Kinematic)
    {
    }

    ~CRigidBody() override = default;

    void Start() override
    {
    };
    void Update() override;

    void CleanUp() override
    {
    };

    //setters
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

    void SetLinearDrag(float drag)
    {
        linear_drag_ = drag;
    }

    void SetAngularDrag(float drag)
    {
        angular_drag_ = drag;
    }

    void SetUseGravity(bool use)
    {
        use_gravity_ = use;
    }

    void SetUseDrag(bool use)
    {
        use_drag_ = use;
    }

    void SetUseAngularDrag(bool use)
    {
        use_angular_drag_ = use;
    }

    void SetConstrainLinearX(bool constrain)
    {
        constrain_linear_x_ = constrain;
    }

    void SetConstrainLinearY(bool constrain)
    {
        constrain_linear_y_ = constrain;
    }

    void SetConstrainLinearZ(bool constrain)
    {
        constrain_linear_z_ = constrain;
    }

    void SetConstrainAngularX(bool constrain)
    {
        constrain_angular_x_ = constrain;
    }

    void SetConstrainAngularY(bool constrain)
    {
        constrain_angular_y_ = constrain;
    }

    void SetConstrainAngularZ(bool constrain)
    {
        constrain_angular_z_ = constrain;
    }

    //getters
    XMFLOAT3 GetLinearVel() const
    {
        return linear_vel_;
    }

    XMFLOAT3 GetAngularVel() const
    {
        return angular_vel_;
    }

    XMFLOAT3 GetLinearAccel() const
    {
        return linear_accel_;
    }

    XMFLOAT3 GetAngularAccel() const
    {
        return angular_accel_;
    }

    XMFLOAT3 GetGravity() const
    {
        return gravity_;
    }

    float GetMass() const
    {
        return mass;
    }

    float GetLinearDrag() const
    {
        return linear_drag_;
    }

    float GetAngularDrag() const
    {
        return angular_drag_;
    }

    bool GetUseGravity() const
    {
        return use_gravity_;
    }

    bool GetUseDrag() const
    {
        return use_drag_;
    }

    bool GetUseAngularDrag() const
    {
        return use_angular_drag_;
    }

    bool GetConstrainLinearX() const
    {
        return constrain_linear_x_;
    }

    bool GetConstrainLinearY() const
    {
        return constrain_linear_y_;
    }

    bool GetConstrainLinearZ() const
    {
        return constrain_linear_z_;
    }

    bool GetConstrainAngularX() const
    {
        return constrain_angular_x_;
    }

    bool GetConstrainAngularY() const
    {
        return constrain_angular_y_;
    }

    bool GetConstrainAngularZ() const
    {
        return constrain_angular_z_;
    }
};
