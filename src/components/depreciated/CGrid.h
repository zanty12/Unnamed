#pragma once
#include "main.h"
#include <vector>

#include "CGridCell.h"
#include "component.h"

//defines a square grid with snapping for objects
class CGrid : public Component
{
private:
    float size_ = 1.0f;
    int x_ = 100;
    int y_ = 100;
    std::vector<std::vector<CGridCell*>> grid_;
public:
    CGrid() : Component("Grid")
    {
        grid_.resize(x_);
        for (int i = 0; i < x_; i++)
        {
            grid_[i].resize(y_);
        }
    }
    CGrid(float size,int x, int y) : Component("Grid"), size_(size), x_(x), y_(y)
    {
        grid_.resize(x);
        for (int i = 0; i < x; i++)
        {
            grid_[i].resize(y);
        }
    }
    bool Insert(CGridCell* object, int x, int y);
    bool Insert(CGridCell* object, float coordx, float coordy);
    XMFLOAT3 GetPosition(int idx, int idy) const;
    void Remove(int x, int y);
    void Start() override{}
    void Update() override{}
    void CleanUp() override;

    float GetSize() const { return size_; }
    int GetX() const { return x_; }
    int GetY() const { return y_; }
    CGridCell* GetCell(int x, int y) { return grid_[x][y]; }
    void SetSize(float size) { size_ = size; }
    void SetX(int x) { x_ = x; }
    void SetY(int y) { y_ = y; }
};
