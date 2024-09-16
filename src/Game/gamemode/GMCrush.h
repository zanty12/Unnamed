#pragma once
#include "Gamemode.h"
class GMCrush :
    public GameMode
{
private:
	int blocks_ = 10000;
public :
	GMCrush() = default;
	~GMCrush() = default;
	void Update() override;
	void SetBlocks(int blocks);
	int GetBlocks() const { return blocks_; }
};

