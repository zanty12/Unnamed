#pragma once
#include "components/CModelRenderer.h"
#include "components/CPhysXRigidBody.h"
#include "traits/debugmenu.h"

class CPlayerMenu : public Component, public DebugMenu
{
public:
    CPlayerMenu() : Component("PlayerMenu", DontCare)
    {
    }

    ~CPlayerMenu() override = default;

    void Start() override
    {
    }

    void Update() override
    {
    }

    void CleanUp() override
    {
    }

    void DrawMenu() override
    {
        ImGui::Begin("Player");
        ImGui::Text("Player Menu");
        Entity* parent = Manager::FindEntityByID(parent_id_);
        if(parent->GetComponent<CPhysXRigidBody>())
        {
            physx::PxRigidActor* actor = parent->GetComponent<CPhysXRigidBody>()->GetActor();
            if(actor->is<physx::PxRigidDynamic>())
            {
                physx::PxRigidDynamic* dynamic = actor->is<physx::PxRigidDynamic>();
                float mass = dynamic->getMass();
                ImGui::Text("Mass: %f", mass);
                float linear_damping = dynamic->getLinearDamping();
                ImGui::Text("Linear Damping: %f", linear_damping);
                float angular_damping = dynamic->getAngularDamping();
                ImGui::Text("Angular Damping: %f", angular_damping);
                physx::PxVec3 linear_velocity = dynamic->getLinearVelocity();
                ImGui::Text("Linear Velocity: %f %f %f", linear_velocity.x, linear_velocity.y, linear_velocity.z);
                physx::PxVec3 angular_velocity = dynamic->getAngularVelocity();
                ImGui::Text("Angular Velocity: %f %f %f", angular_velocity.x, angular_velocity.y, angular_velocity.z);
                bool enable_gravity = dynamic->getActorFlags() & physx::PxActorFlag::eDISABLE_GRAVITY ? false : true;
                ImGui::Text("Enable Gravity: %s", enable_gravity ? "true" : "false");
                physx::PxTransform global_position = dynamic->getGlobalPose();
                ImGui::Text("Global Position: %f %f %f", global_position.p.x, global_position.p.y, global_position.p.z);
                physx::PxQuat global_rotation = global_position.q;
                ImGui::Text("Global Rotation: %f %f %f %f", global_rotation.x, global_rotation.y, global_rotation.z, global_rotation.w);
            }

        }
        Transform* transform = parent->GetTransform();
        XMFLOAT3 position = transform->position;
        ImGui::Text("Entity Position: %f %f %f", position.x, position.y, position.z);
        XMFLOAT3 rotation = transform->rotation;
        ImGui::Text("Entity Rotation: %f %f %f", rotation.x, rotation.y, rotation.z);
        XMFLOAT3 scale = transform->scale;
        ImGui::Text("Entity Scale: %f %f %f", scale.x, scale.y, scale.z);
        XMFLOAT4 quat = transform->quaternion;
        ImGui::Text("Entity Quat: %f %f %f %f", quat.x, quat.y, quat.z, quat.w);
        Transform* model = parent->GetComponent<CModelRenderer>()->GetLocalTransform();
        XMFLOAT3 model_position = model->position;
        ImGui::Text("Model Position: %f %f %f", model_position.x, model_position.y, model_position.z);
        XMFLOAT3 model_rotation = model->rotation;
        ImGui::Text("Model Rotation: %f %f %f", model_rotation.x, model_rotation.y, model_rotation.z);
        XMFLOAT3 model_scale = model->scale;
        ImGui::Text("Model Scale: %f %f %f", model_scale.x, model_scale.y, model_scale.z);
        ImGui::End();
    }
};
