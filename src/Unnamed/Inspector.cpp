#include <Inspector.h>
#include "imgui_impl_hal.h"
#include "manager.h"

std::vector<Window> Inspector::windows_;
Entity* Inspector::selected_entity_ = nullptr;

void Inspector::Register(Window window)
{
    windows_.push_back(window);
}

void Inspector::DrawInspector()
{
    //draw basic hierarchy
    ImGui::Begin("Scene Hierarchy");
    //get all entities
    std::vector<Entity*> entities = Manager::GetEntities();
    //draw a tree of entities
    for (auto entity : entities)
    {
        //set all nodes to be leaves
        ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_Leaf;
        //if entity is selected, set it to be selected
        if (selected_entity_ == entity)
        {
            flag |= ImGuiTreeNodeFlags_Selected;
        }
        if (ImGui::TreeNodeEx(entity->GetName().c_str(), flag))
        {
            if (ImGui::IsItemClicked())
            {
                selected_entity_ = entity;
            }
            ImGui::TreePop();
        }
    }
    ImGui::End();
    //draw inspector
    ImGui::Begin("Inspector");
    if (selected_entity_)
    {
        //transform tree node
        if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        {
            Transform transform = selected_entity_->GetTransform();
            ImGui::Text("Position");
            ImGui::DragFloat3("##position", &transform.position.x, 0.1f);
            ImGui::Text("Rotation");
            //convert quaternion to euler angles
            XMFLOAT3 euler;
            euler = Transform::QuatToEuler(transform.quaternion);
            ImGui::DragFloat3("##rotation", &euler.x, 0.1f);
            //convert euler angles back to quaternion
            transform.quaternion = Transform::EulerToQuat(euler);
            ImGui::Text("Scale");
            ImGui::DragFloat3("##scale", &transform.scale.x, 0.1f);
            ImGui::TreePop();
        }
        //draw components
        for (auto component : selected_entity_->GetComponents())
        {
            if (ImGui::TreeNodeEx(component->GetType().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                component->InspectorWindow();
                ImGui::TreePop();
            }
        }
    }
    ImGui::End();
}
