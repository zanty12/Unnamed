#include "manager.h"
#include "Component.h"

#include "imgui_impl_hal.h"

void Component::InspectorWindow()
{
    //node is made outside in inspector class already so we only add the stuff we want to show
    //local transform
    ImGui::Text("Position");
    ImGui::DragFloat3("##position", &local_transform_.position.x, 0.1f);
    ImGui::Text("Rotation");
    //convert quaternion to euler angles
    XMFLOAT3 euler;
    euler = Transform::QuatToEuler(local_transform_.quaternion);
    ImGui::DragFloat3("##rotation", &euler.x, 0.1f);
    //convert euler angles back to quaternion
    local_transform_.quaternion = Transform::EulerToQuat(euler);
    ImGui::Text("Scale");
    ImGui::DragFloat3("##scale", &local_transform_.scale.x, 0.1f);


}

Transform Component::GetWorldTransform() const{
    //Get parent's world transform
    Transform parent_transform = parent_entity_->GetTransform();
    Transform world_transform = Transform::ToWorld(parent_transform, local_transform_);
    return world_transform;
}
