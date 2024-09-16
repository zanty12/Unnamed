#pragma once
#include "components/Component.h"
#include "system/timesystem.h"
#include "manager.h"


class CExplosionBehaviour : public Component
{
private:
	float timer_ = 1.0f;
public:
	CExplosionBehaviour() : Component("ExplosionBehaviour", PostPhysicsBehaviour)
	{
	}
	~CExplosionBehaviour() override = default;
	void Start() override {}
	void Update() override {
		timer_ -= Time::GetDeltaTime();
		if (timer_ < 0)
		{
			Manager::QueueForRemoval(parent_id_);
		}
	}
	void CleanUp() override {}
};

