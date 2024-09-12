#include "physicssystem3D.h"

#include <algorithm>

#include "manager.h"
#include "components/depreciated/CCollider3D.h"

std::vector<Physics3D*> PhysicsSystem3D::physics3D_;
void PhysicsSystem3D::AddCollider3D(Physics3D* physics3D)
{
    physics3D_.push_back(physics3D);
    //remove duplicates
    physics3D_.erase(std::unique(physics3D_.begin(), physics3D_.end()), physics3D_.end());
}

void PhysicsSystem3D::RemoveCollider3D(Physics3D* physics3D)
{
    physics3D_.erase(std::remove(physics3D_.begin(), physics3D_.end(), physics3D), physics3D_.end());
}

std::vector<Physics3D*> PhysicsSystem3D::GetPhysics3D()
{
    return physics3D_;
}

void PhysicsSystem3D::UpdateCollisions()
{
    for(auto physics3D : physics3D_)
        {
        //dynamic_cast<CCollider3D*>(physics3D)->UpdateCollision();
        //use threadpool to update collisions
        CCollider3D* collider = dynamic_cast<CCollider3D*>(physics3D);
        Manager::GetThreadPool().Enqueue(process_priority.at("CollisionCheck"),[collider](){
            collider->UpdateCollision();
        });
    }
}

void PhysicsSystem3D::ApplyCollisions()
{
    for(auto physics3D : physics3D_)
    {
        //dynamic_cast<CCollider3D*>(physics3D)->ApplyCollision();
        //use threadpool to apply collisions
        CCollider3D* collider = dynamic_cast<CCollider3D*>(physics3D);
        Manager::GetThreadPool().Enqueue(process_priority.at("CollisionApply"),[collider](){
            collider->ApplyCollision();
        });
    }
}

void PhysicsSystem3D::CleanUp()
{
    physics3D_.clear();
}
