#include "main.h"
#include "system/input.h"
#include "manager.h"
#include "CPlayerController.h"

#include "CAudio.h"
#include "CCamera.h"
#include "entity.h"
#include "CRigidBody.h"
#include "system/timesystem.h"
#include "objects/bullet.h"

void CPlayerController::Update()
{
    //find parent
    Entity* parent = Manager::FindEntityByID(parent_id_);
    parent->Lock();
    if (parent_id_ < 0 || parent == nullptr)
    {
        //do nothing
    }
    else
    {
        //get camera component
        CCamera* camera = parent->GetComponent<CCamera>();
        XMFLOAT3 camera_pos = camera->GetPosition();
        XMFLOAT3 parent_pos = parent->GetTransform()->position;
        float dt = Time::GetDeltaTime();

        //rotate camera with arrow keys
        if (Input::GetKeyPress(VK_LEFT))
        {
            //Rotate camera around parent
            XMFLOAT3 new_cam_pos = Transform::RotatePointAroundTarget(camera_pos, parent_pos,
                                                                      3.14f * Time::GetDeltaTime(),
                                                                      XMFLOAT3(0.0f, 1.0f, 0.0f));
            //set new camera offset
            camera->SetOffset(XMFLOAT3(new_cam_pos.x - parent_pos.x,
                                       new_cam_pos.y - parent_pos.y,
                                       new_cam_pos.z - parent_pos.z));
        }
        if (Input::GetKeyPress(VK_RIGHT))
        {
            //Rotate camera around parent
            XMFLOAT3 new_cam_pos = Transform::RotatePointAroundTarget(camera_pos, parent_pos,
                                                                      -3.14f * Time::GetDeltaTime(),
                                                                      XMFLOAT3(0.0f, 1.0f, 0.0f));
            //set new camera offset
            camera->SetOffset(XMFLOAT3(new_cam_pos.x - parent_pos.x,
                                       new_cam_pos.y - parent_pos.y,
                                       new_cam_pos.z - parent_pos.z));
        }
        if (Input::GetKeyPress(VK_UP))
        {
            //calculate rotation axis
            XMFLOAT3 axis;
            XMStoreFloat3(&axis, XMLoadFloat3(&camera_pos) - XMLoadFloat3(&(parent_pos)));
            axis = Transform::GetRight(axis);
            XMStoreFloat3(&axis, XMVector3Normalize(XMLoadFloat3(&axis)));
            //Rotate camera around parent
            XMFLOAT3 new_cam_pos = Transform::RotatePointAroundTarget(camera_pos, parent_pos,
                                                                      3.14f * Time::GetDeltaTime(), axis);
            //set new camera offset
            camera->SetOffset(XMFLOAT3(new_cam_pos.x - parent_pos.x,
                                       new_cam_pos.y - parent_pos.y,
                                       new_cam_pos.z - parent_pos.z));
        }
        if (Input::GetKeyPress(VK_DOWN))
        {
            //calculate rotation axis
            XMFLOAT3 axis;
            XMStoreFloat3(&axis, XMLoadFloat3(&camera_pos) - XMLoadFloat3(&(parent_pos)));
            axis = Transform::GetRight(axis);
            axis = XMFLOAT3(axis.x, 0.0f, axis.z);
            //normalize axis
            XMStoreFloat3(&axis, XMVector3Normalize(XMLoadFloat3(&axis)));
            //Rotate camera around parent
            XMFLOAT3 new_cam_pos = Transform::RotatePointAroundTarget(camera_pos, parent_pos,
                                                                      -3.14f * Time::GetDeltaTime(), axis);
            //set new camera offset
            camera->SetOffset(XMFLOAT3(new_cam_pos.x - parent_pos.x,
                                       new_cam_pos.y - parent_pos.y,
                                       new_cam_pos.z - parent_pos.z));
        }

        //move parent with keyboard input
        if (Input::GetKeyPress('W'))
        {
            //Get vector between camera and parent
            XMFLOAT3 forward;
            XMStoreFloat3(&forward, XMLoadFloat3(&camera_pos) - XMLoadFloat3(&parent_pos));
            XMStoreFloat3(&forward, XMVector3Normalize(XMLoadFloat3(&forward)));
            XMStoreFloat3(&forward, XMLoadFloat3(&forward) * dt * -10);
            Transform::MoveBy(parent->GetTransform(), forward);
            //rotate parent to face forward
            Transform::RotateTo(parent->GetTransform(), XMFLOAT3(0.0f, atan2(-forward.x, -forward.z), 0.0f));
        }
        if (Input::GetKeyPress('S'))
        {
            XMFLOAT3 forward;
            XMStoreFloat3(&forward, XMLoadFloat3(&camera_pos) - XMLoadFloat3(&parent_pos));
            XMStoreFloat3(&forward, XMVector3Normalize(XMLoadFloat3(&forward)));
            XMStoreFloat3(&forward, XMLoadFloat3(&forward) * dt * 10);
            Transform::MoveBy(parent->GetTransform(), forward);
            //rotate parent to face backward
            Transform::RotateTo(parent->GetTransform(), XMFLOAT3(0.0f, atan2(-forward.x, -forward.z), 0.0f));
        }
        if (Input::GetKeyPress('A'))
        {
            XMFLOAT3 forward;
            XMStoreFloat3(&forward, XMLoadFloat3(&camera_pos) - XMLoadFloat3(&parent_pos));
            XMFLOAT3 right = Transform::GetRight(forward);
            XMStoreFloat3(&right, XMLoadFloat3(&right) * dt * 10);
            Transform::MoveBy(parent->GetTransform(), right);
            //rotate parent to face left
            Transform::RotateTo(parent->GetTransform(), XMFLOAT3(0.0f, atan2(-right.x, -right.z), 0.0f));
        }
        if (Input::GetKeyPress('D'))
        {
            XMFLOAT3 forward;
            XMStoreFloat3(&forward, XMLoadFloat3(&camera_pos) - XMLoadFloat3(&parent_pos));
            XMFLOAT3 right = Transform::GetRight(forward);
            XMStoreFloat3(&right, XMLoadFloat3(&right) * dt * -10);
            Transform::MoveBy(parent->GetTransform(), right);
            //rotate parent to face right
            Transform::RotateTo(parent->GetTransform(), XMFLOAT3(0.0f, atan2(-right.x, -right.z), 0.0f));
        }

        //jump
        if (Input::GetKeyTrigger(VK_SPACE))
        {
            CRigidBody* rigidBody = parent->GetComponent<CRigidBody>();
            if (parent->GetComponent<CRigidBody>() != nullptr)
                rigidBody->SetLinearVel(XMFLOAT3(0.0f, 10.0f, 0.0f));
        }
        //shoot bullet
        if (Input::GetKeyTrigger('G'))
        {
            Bullet* bullet = new Bullet();
            parent->GetComponent<CAudio>()->Play();
            //Get forward vector of parent
            XMFLOAT3 forward = Transform::GetForward(parent->GetTransform());
            //normalize forward vector
            XMStoreFloat3(&forward, XMVector3Normalize(XMLoadFloat3(&forward)));
            //set bullet velocity to forward vector
            forward = XMFLOAT3(-forward.x * 5.0f, forward.y * 5.0f, -forward.z * 5.0f);
            bullet->SetVelocity(forward);
            XMFLOAT3 bullet_pos = parent_pos;
            bullet_pos.y += 1.0f;
            bullet->SetPosition(bullet_pos);
            bullet->QueueSpawn();
        }
    }
    parent->Unlock();
}
