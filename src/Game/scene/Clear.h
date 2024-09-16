#pragma once
#include "scene.h"
class Clear :
    public Scene
{
public:
	Clear() = default;
	~Clear() override = default;
	void Setup() override;
};

