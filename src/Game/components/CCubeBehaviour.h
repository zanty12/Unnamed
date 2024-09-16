#pragma once
#include "components/Component.h"

class CCubeBehaviour : public Component
{
private:
    physx::PxRigidDynamic* rigid_body_ = nullptr;
	bool destroyed_ = false;
public:
    CCubeBehaviour() : Component("CCubeBehaviour",PostPhysicsBehaviour){}
    void Start() override;
    void Update() override;
    void CleanUp() override{}
};
