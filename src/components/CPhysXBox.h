#pragma once
#include <GeometricPrimitive.h>

#include "component.h"
#include "PxActor.h"
#include "traits/drawable.h"

class CPhysXBox : public Component, public Drawable
{
private:
    physx::PxShape* shape_ = nullptr;
    bool view_ = false;
    std::unique_ptr<DirectX::GeometricPrimitive> debug_shape_;
public:
    CPhysXBox() : Component("PhysXPrimitive"),Drawable(10) {}
    ~CPhysXBox() override = default;
    void Start() override;
    void Update() override{}
    void CleanUp() override;
    void Draw() override;
    void SetView(bool view) { view_ = view; }
};
