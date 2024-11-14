#include "manager.h"
#include "Component.h"

Transform Component::GetWorldTransform() const{
    //Get parent's world transform
    Transform parent_transform = parent_entity_->GetTransform();
    Transform world_transform = Transform::ToWorld(parent_transform, local_transform_);
    return world_transform;
}