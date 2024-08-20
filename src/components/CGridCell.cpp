#include "CGridCell.h"
#include "CGrid.h"
#include "manager.h"

void CGridCell::Update()
{
    if (active_)
    {
        //snap parent to grid
        Transform* transform = Manager::FindEntityByID(parent_id_)->GetTransform();
        Transform::MoveTo(transform, grid_->GetPosition(x_,y_));
    }
}


void CGridCell::Attach(CGrid* grid)
{
    grid_ = grid;
    Transform* transform = Manager::FindEntityByID(parent_id_)->GetTransform();
    if (grid->Insert(this, transform->position.x, transform->position.y))
    {
        x_ = static_cast<int>(ceil(transform->position.x / grid->GetSize()) - 1);
        y_ = static_cast<int>(ceil(transform->position.y / grid->GetSize()) - 1);
    }
    else
    {
        active_ = false;
    }
}
