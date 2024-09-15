#include "CPinballBehaviour.h"
#include "Manager.h"
#include "components/CPhysXSphere.h"
#include "system/input.h"

void CPinballBehaviour::Start()
{
    rigidBody_ = Manager::FindEntityByID(parent_id_)->GetComponent<CPhysXRigidBody>()->GetActor()->is<physx::PxRigidDynamic>();
    shape_ = Manager::FindEntityByID(parent_id_)->GetComponent<CPhysXSphere>()->GetShape();
}

void CPinballBehaviour::Update()
{
    //ready to shoot when linear velocity is 0
    if (rigidBody_->getLinearVelocity().magnitude() < 3.0f)
    {
        //get mouse position
        if(Input::GetMouseButtonPress(LEFT_BUTTON) && !pull_back_)
        {
            start_mouse_ = XMINT2(Input::GetMousePos().x, Input::GetMousePos().y);
            pull_back_ = true;
        }
        if(pull_back_){
            auto mouse_pos = Input::GetMousePos();
            auto diff = XMINT2(mouse_pos.x - start_mouse_.x, mouse_pos.y - start_mouse_.y);
            //calculate force
            auto force = XMINT2(diff.x * 100, diff.y * 100);
            if(!Input::GetMouseButtonPress(LEFT_BUTTON))
            {
                pull_back_ = false;
                //apply force
                rigidBody_->addForce(physx::PxVec3(-force.x, 0, force.y));
            }
        }
    }
}

void CPinballBehaviour::CleanUp()
{
}

void CPinballBehaviour::DrawMenu()
{
    ImGui::Begin("Pinball Behaviour");
    ImGui::Checkbox("Pull Back", &pull_back_);
    ImGui::Text("Start Mouse: %d, %d", start_mouse_.x, start_mouse_.y);
    ImGui::Text("Linear Velocity: %f", rigidBody_->getLinearVelocity().magnitude());
    ImGui::End();
}
