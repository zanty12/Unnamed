#pragma once
#include "components/Component.h"
class CPhysXCharacterController :
    public Component
{
public:
	CPhysXCharacterController() : Component("CPhysXCharacterController",Kinematic) {};
	void Start() override;
	void Update() override;
	void CleanUp() override;
};

