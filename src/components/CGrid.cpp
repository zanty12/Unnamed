#include "CGrid.h"

bool CGrid::Insert(CGridSnap* object, int x, int y)
{
    if(grid_[x][y])
        return false;
    grid_[x][y] = object;
    return true;
}

void CGrid::Remove(int x, int y)
{
    if(grid_[x][y])
        grid_[x][y] = nullptr;
}
