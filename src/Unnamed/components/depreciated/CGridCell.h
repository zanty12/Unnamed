#pragma once
#include "components/component.h"

class CGrid;
class CGridCell: public Component
{
private:
    CGrid* grid_ = nullptr;
    int x_ = 0;
    int y_ = 0;
    bool active_ = true;
public:
    CGridCell() : Component("GridCell",PostPhysicsBehaviour){}
    void Start() override{};
    void Update() override;
    void Attach(CGrid* grid);
};
