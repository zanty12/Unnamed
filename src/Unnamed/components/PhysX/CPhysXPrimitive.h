#pragma once

#include <memory>
#include "system/PhysX_Impl.h"
#include "components/Component.h"
#include "traits/drawable.h"

#include <DirectXTK/GeometricPrimitive.h>

#pragma comment (lib, "DirectXTK.lib")

class CPhysXPrimitive : public Component, public Drawable
{
protected:
    physx::PxShape* shape_ = nullptr;
    bool is_trigger_ = false;
    bool simulate_ = true;
    bool query_ = true;
    bool debug_view_ = false;
    physx::PxRigidActor* actor_ = nullptr;
    std::unique_ptr<DirectX::GeometricPrimitive> debug_shape_;
    float static_friction_ = 0.5f;
    float dynamic_friction_ = 0.5f;
    float restitution_ = 0.5f;
	bool contact_ = false;


public:
    CPhysXPrimitive() : Component("PhysXPrimitive",Kinematic), Drawable(10)
    {
    }

    virtual ~CPhysXPrimitive() = default;
    virtual void Start() = 0;

    void Update() override
    {
    }

    virtual void CleanUp() = 0;
    void Draw();
    void SetDebugView(bool view) { debug_view_ = view; }
    void SetIsTrigger(bool is_trigger) { is_trigger_ = is_trigger; simulate_ = !is_trigger; }
    void SetSimulate(bool simulate) { simulate_ = simulate; is_trigger_ = !simulate; }
    void SetQuery(bool query) { query_ = query; }
    void SetMaterial(float static_friction = 0.5f, float dynamic_friction = 0.5f, float restitution = 0.5f)
    {
        static_friction_ = static_friction;
        dynamic_friction_ = dynamic_friction;
        restitution_ = restitution;
    }

	void SetContact(bool contact) { contact_ = contact; }

    physx::PxShape* GetShape() const { return shape_; }
};
