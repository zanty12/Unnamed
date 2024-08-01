#include "CGrid.h"

bool CGrid::Insert(CGridCell* object, int idx, int idy)
{
    if (grid_[idx][idy])
        return false;
    grid_[idx][idy] = object;
    return true;
}

bool CGrid::Insert(CGridCell* object, float coordx, float coordy)
{
    return Insert(object, static_cast<int>(ceil(coordx / size_) - 1), static_cast<int>(ceil(coordy / size_) - 1));
}

XMFLOAT3 CGrid::GetPosition(int idx, int idy) const
{
    return {size_ / 2 * static_cast<float>(idx + 1), size_ / 2 * static_cast<float>(idy + 1), 0.0f};
}

void CGrid::Remove(int x, int y)
{
    if (grid_[x][y])
        grid_[x][y] = nullptr;
}

void CGrid::CleanUp()
{
    grid_.clear();
}
