#include "main.h"
#include "input.h"
#include "manager.h"
#include "playercontroller.h"

#include "camera.h"
#include "entity.h"
#include "rigidbody.h"
#include "timesystem.h"
#include "objects/bullet.h"

void PlayerController::Update()
{
    //find parent
    Entity* parent = Manager::FindEntity(parent_id_);
    if (parent_id_ < 0 || parent == nullptr)
    {
        //do nothing
    }
    else
    {
        //get camera component
        Camera* camera = parent->GetComponent<Camera>();
        //move parent with keyboard input
        if (Input::GetKeyPress('W'))
        {
            Transform::MoveBy(parent->GetTransform(), DirectX::XMFLOAT3(0.0f, 0.0f, 0.1f));
        }
        if (Input::GetKeyPress('S'))
        {
            Transform::MoveBy(parent->GetTransform(), DirectX::XMFLOAT3(0.0f, 0.0f, -0.1f));
        }
        if (Input::GetKeyPress('A'))
        {
            Transform::MoveBy(parent->GetTransform(), DirectX::XMFLOAT3(-0.1f, 0.0f, 0.0f));
        }
        if (Input::GetKeyPress('D'))
        {
            Transform::MoveBy(parent->GetTransform(), DirectX::XMFLOAT3(0.1f, 0.0f, 0.0f));
        }
        //rotate camera with arrow keys
        /*if (Input::GetKeyPress(VK_LEFT))
        {
            //Get camera position
            XMFLOAT3 camera_pos = camera->GetPosition();
            //Rotate camera around parent
            XMFLOAT3 new_cam_pos = Transform::RotatePointAroundTarget(camera_pos, parent->GetTransform()->position,
                                                                      3.14f * Time::GetDeltaTime(),
                                                                      XMFLOAT3(0.0f, 0.1f, 0.0f));
            //set new camera offset
            camera->SetOffset(XMFLOAT3(new_cam_pos.x - parent->GetTransform()->position.x,
                                       new_cam_pos.y - parent->GetTransform()->position.y,
                                       new_cam_pos.z - parent->GetTransform()->position.z));
        }
        if (Input::GetKeyPress(VK_RIGHT))
        {
            //Get camera position
            XMFLOAT3 camera_pos = camera->GetPosition();
            //Rotate camera around parent
            XMFLOAT3 new_cam_pos = Transform::RotatePointAroundTarget(camera_pos, parent->GetTransform()->position,
                                                                      -3.14f * Time::GetDeltaTime(),
                                                                      XMFLOAT3(0.0f, 0.1f, 0.0f));
            //set new camera offset
            camera->SetOffset(XMFLOAT3(new_cam_pos.x - parent->GetTransform()->position.x,
                                       new_cam_pos.y - parent->GetTransform()->position.y,
                                       new_cam_pos.z - parent->GetTransform()->position.z));
        }
        if (Input::GetKeyPress(VK_UP))
        {
            //Get camera position
            XMFLOAT3 camera_pos = camera->GetPosition();
            //calculate rotation axis
            XMFLOAT3 axis;
            XMStoreFloat3(&axis,XMLoadFloat3(&camera_pos)-XMLoadFloat3(&(parent->GetTransform()->position)));
            axis = Transform::GetRight(axis);ww
            XMStoreFloat3(&axis, XMVector3Normalize(XMLoadFloat3(&axis)));
            //Rotate camera around parent
            XMFLOAT3 new_cam_pos = Transform::RotatePointAroundTarget(camera_pos, parent->GetTransform()->position,
                                                                      3.14f * Time::GetDeltaTime(), axis);
            //set new camera offset
            camera->SetOffset(XMFLOAT3(new_cam_pos.x - parent->GetTransform()->position.x,
                                       new_cam_pos.y - parent->GetTransform()->position.y,
                                       new_cam_pos.z - parent->GetTransform()->position.z));
        }
        if (Input::GetKeyPress(VK_DOWN))
        {
            //Get camera position
            XMFLOAT3 camera_pos = camera->GetPosition();
            //calculate rotation axis
            XMFLOAT3 axis;
            XMStoreFloat3(&axis,XMLoadFloat3(&camera_pos)-XMLoadFloat3(&(parent->GetTransform()->position)));
            axis = Transform::GetRight(axis);
            axis = XMFLOAT3(axis.x, 0.0f, axis.z);
            //normalize axis
            XMStoreFloat3(&axis, XMVector3Normalize(XMLoadFloat3(&axis)));
            //Rotate camera around parent
            XMFLOAT3 new_cam_pos = Transform::RotatePointAroundTarget(camera_pos, parent->GetTransform()->position,
                                                                      -3.14f * Time::GetDeltaTime(), axis);
            //set new camera offset
            camera->SetOffset(XMFLOAT3(new_cam_pos.x - parent->GetTransform()->position.x,
                                       new_cam_pos.y - parent->GetTransform()->position.y,
                                       new_cam_pos.z - parent->GetTransform()->position.z));
        }*/
        //jump
        if (Input::GetKeyPress(VK_SPACE))
        {
            RigidBody* rigidBody = parent->GetComponent<RigidBody>();
            if (parent->GetComponent<RigidBody>() != nullptr)
                rigidBody->SetLinearVel(XMFLOAT3(0.0f, 10.0f, 0.0f));
        }
        //shoot bullet
        if (Input::GetKeyTrigger('G'))
        {
            Bullet* bullet = new Bullet();
            //Get forward vector of parent
            XMFLOAT3 forward = Transform::GetForward(parent->GetTransform());
            //normalize forward vector with XMFLOAT3
            XMStoreFloat3(&forward, XMVector3Normalize(XMLoadFloat3(&forward)));
            //set bullet velocity to forward vector
            forward = XMFLOAT3(forward.x * 2.0f, forward.y * 2.0f, forward.z * 2.0f);
            bullet->SetVelocity(forward);
            bullet->SetPosition(parent->GetTransform()->position);
            bullet->QueueSpawn();
        }
    }
}
