#pragma once
#include "Component.h"
class CPhysXCharacterController :
    public Component
{
public:
	CPhysXCharacterController() : Component("CPhysXCharacterController") {};
	void Start() override;
	void Update() override;
	void CleanUp() override;
};

