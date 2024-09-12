#pragma once

#include <memory>
#include "system/PhysX_Impl.h"
#include "component.h"
#include "traits/drawable.h"

#include <DirectXTK/GeometricPrimitive.h>

#pragma comment (lib, "DirectXTK.lib")



class CPhysXPrimitive : public Component, public Drawable
{
protected:
    physx::PxShape* shape_ = nullptr;
    bool debug_view_ = false;
    std::unique_ptr<DirectX::GeometricPrimitive> debug_shape_;

public:
    CPhysXPrimitive() : Component("PhysXPrimitive"), Drawable(10)
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
};
