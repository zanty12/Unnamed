#pragma once
#include <vector>

#include "CGridSnap.h"
#include "component.h"

//defines a square grid with snapping for objects
class CGrid : public Component
{
private:
    float size_ = 1.0f;
    int x = 100;
    int y = 100;
    std::vector<std::vector<CGridSnap*>> grid_;
public:
    CGrid() : Component("Grid")
    {
        grid_.resize(x);
        for (int i = 0; i < x; i++)
        {
            grid_[i].resize(y);
        }
    }
    CGrid(float size,int x, int y) : Component("Grid"), size_(size), x(x), y(y)
    {
        grid_.resize(x);
        for (int i = 0; i < x; i++)
        {
            grid_[i].resize(y);
        }
    }
    bool Insert(CGridSnap* object, int x, int y);
    void Remove(int x, int y);
    void Start() override{}
    void Update() override{}
};
