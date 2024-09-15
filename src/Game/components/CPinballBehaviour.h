#pragma once
#include "components/Component.h"
#include "components/CPhysXRigidBody.h"
#include "traits/DebugMenu.h"

class CPinballBehaviour : public Component, public DebugMenu
{
private:
    physx::PxRigidDynamic* rigidBody_ = nullptr;
    physx::PxShape* shape_ = nullptr;
    bool pull_back_ = false;
    XMINT2 start_mouse_ = {0,0};
public:
    CPinballBehaviour() : Component("PinballBehaviour",PostPhysicsBehaviour) {};
    ~CPinballBehaviour() = default;
    void Start();
    void Update() override;
    void CleanUp() override;
    void DrawMenu() override;
};
