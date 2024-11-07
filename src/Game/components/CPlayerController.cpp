#include "main.h"
#include "system/input.h"
#include "manager.h"
#include "CPlayerController.h"

#include "components/CAudio.h"
#include "components/CCamera.h"
#include "entity.h"
#include "system/timesystem.h"
#include "prefab/bullet.h"
#include <components/CPhysXRigidBody.h>

#include "components/CAnimationModel.h"
#include "components/CTerrain.h"

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
        XMFLOAT3 camera_pos = camera->GetWorldTransform().position;
        XMFLOAT3 parent_pos = parent->GetTransform().position;
		CPhysXRigidBody* rigidBody = parent->GetComponent<CPhysXRigidBody>();
        physx::PxRigidDynamic *actor = rigidBody->GetActor()->is<physx::PxRigidDynamic>();

        //rotate camera with arrow keys
        if (Input::GetKeyPress(VK_LEFT))
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
        if (Input::GetKeyPress(VK_RIGHT))
        {
            //Rotate camera around parent
            XMFLOAT3 new_cam_pos = Transform::RotatePointAroundTarget(camera_pos, parent_pos,
                                                                      +3.14f * Time::GetDeltaTime(),
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

        /*if(Input::GetKeyPress('W'))
        {
            Transform::MoveBy(parent->GetTransform(), XMFLOAT3(0.0f, 0.0f, 0.1f));
            XMVECTOR quat = XMQuaternionRotationRollPitchYaw(0.1f, 0.0f, 0.0f);
            quat = XMQuaternionMultiply(XMLoadFloat4(&(parent->GetTransform()->quaternion)), quat);
            XMStoreFloat4(&(parent->GetTransform()->quaternion), quat);
            //Transform::RotateBy(parent->GetTransform(), XMFLOAT3(0.1f, 0.0f, 0.0f));
        }
        if(Input::GetKeyPress('S'))
        {
            Transform::MoveBy(parent->GetTransform(), XMFLOAT3(0.0f, 0.0f, -0.1f));
            XMVECTOR quat = XMQuaternionRotationRollPitchYaw(-0.1f, 0.0f, 0.0f);
            quat = XMQuaternionMultiply(XMLoadFloat4(&(parent->GetTransform()->quaternion)), quat);
            XMStoreFloat4(&(parent->GetTransform()->quaternion), quat);
            //Transform::RotateBy(parent->GetTransform(), XMFLOAT3(-0.1f, 0.0f, 0.0f));
        }
        if(Input::GetKeyPress('A'))
        {
            Transform::MoveBy(parent->GetTransform(), XMFLOAT3(-0.1f, 0.0f, 0.0f));
            XMVECTOR quat = XMQuaternionRotationRollPitchYaw(0.0f, 0.0f, 0.1f);
            quat = XMQuaternionMultiply(XMLoadFloat4(&(parent->GetTransform()->quaternion)), quat);
            XMStoreFloat4(&(parent->GetTransform()->quaternion), quat);
            //Transform::RotateBy(parent->GetTransform(), XMFLOAT3(0.0f, 0.0f, 0.1f));
        }
        if(Input::GetKeyPress('D'))
        {
            Transform::MoveBy(parent->GetTransform(), XMFLOAT3(0.1f, 0.0f, 0.0f));
            XMVECTOR quat = XMQuaternionRotationRollPitchYaw(0.0f, 0.0f, -0.1f);
            quat = XMQuaternionMultiply(XMLoadFloat4(&(parent->GetTransform()->quaternion)), quat);
            XMStoreFloat4(&(parent->GetTransform()->quaternion), quat);
            //Transform::RotateBy(parent->GetTransform(), XMFLOAT3(0.0f, 0.0f, -0.1f));
        }*/

        //move parent with keyboard input
        if (Input::GetKeyPress('W'))
        {
            //Get vector between camera and parent
            XMFLOAT3 forward;
            XMStoreFloat3(&forward, XMLoadFloat3(&camera_pos) - XMLoadFloat3(&parent_pos));
            XMStoreFloat3(&forward, XMVector3Normalize(XMLoadFloat3(&forward)));
            XMStoreFloat3(&forward, XMLoadFloat3(&forward)  * -10);
			forward.y = 0.0f;
            //Transform::MoveBy(parent->GetTransform(), forward);
			rigidBody->SetLinearVelocity(forward);
            //actor->setKinematicTarget(physx::PxTransform(forward.x, forward.y, forward.z));
            //rotate parent to face forward
            XMFLOAT3 rot = XMFLOAT3(0.0f, atan2(-forward.x, -forward.z), 0.0f);
            //calculate quaternion from euler angles
            XMVECTOR quat = XMQuaternionRotationRollPitchYaw(rot.x, rot.y, rot.z);
            XMFLOAT4 quat_f;
            XMStoreFloat4(&quat_f, quat);
            //set parent rotation
            Transform::RotateToQuat(parent->GetTransform(),quat_f);
            rigidBody->SetGlobalRotation(quat_f);
            forward_ = 1;
        }
        if (Input::GetKeyPress('S'))
        {
            XMFLOAT3 forward;
            XMStoreFloat3(&forward, XMLoadFloat3(&camera_pos) - XMLoadFloat3(&parent_pos));
            XMStoreFloat3(&forward, XMVector3Normalize(XMLoadFloat3(&forward)));
            XMStoreFloat3(&forward, XMLoadFloat3(&forward)  * 10);
            forward.y = 0.0f;
            //Transform::MoveBy(parent->GetTransform(), forward);
            rigidBody->SetLinearVelocity(forward);
            //rotate parent to face backward
            XMFLOAT3 rot = XMFLOAT3(0.0f, atan2(-forward.x, -forward.z), 0.0f);
            //calculate quaternion from euler angles
            XMVECTOR quat = XMQuaternionRotationRollPitchYaw(rot.x, rot.y, rot.z);
            XMFLOAT4 quat_f;
            XMStoreFloat4(&quat_f, quat);
            //set parent rotation
            Transform::RotateToQuat(parent->GetTransform(),quat_f);
            rigidBody->SetGlobalRotation(quat_f);
            forward_ = -1;
        }
        if (Input::GetKeyPress('A'))
        {
            XMFLOAT3 forward;
            XMStoreFloat3(&forward, XMLoadFloat3(&camera_pos) - XMLoadFloat3(&parent_pos));
            XMFLOAT3 right = Transform::GetRight(forward);
            //move right
            XMStoreFloat3(&right, XMLoadFloat3(&right)  * 10);
            right.y = 0.0f;
            rigidBody->SetLinearVelocity(right);
            //Transform::MoveBy(parent->GetTransform(), right);
            //rotate parent to face left
            XMFLOAT3 rot = XMFLOAT3(0.0f, atan2(-right.x, -right.z), 0.0f);
            //calculate quaternion from euler angles
            XMVECTOR quat = XMQuaternionRotationRollPitchYaw(rot.x, rot.y, rot.z);
            XMFLOAT4 quat_f;
            XMStoreFloat4(&quat_f, quat);
            //set parent rotation
            Transform::RotateToQuat(parent->GetTransform(),quat_f);
           rigidBody->SetGlobalRotation(quat_f);
        }
        if (Input::GetKeyPress('D'))
        {
            XMFLOAT3 forward;
            XMStoreFloat3(&forward, XMLoadFloat3(&camera_pos) - XMLoadFloat3(&parent_pos));
            XMFLOAT3 right = Transform::GetRight(forward);
            //move left
            XMStoreFloat3(&right, XMLoadFloat3(&right) * -10);
            right.y = 0.0f;
            rigidBody->SetLinearVelocity(right);
            //Transform::MoveBy(parent->GetTransform(), right);
            //rotate parent to face right
            XMFLOAT3 rot = XMFLOAT3(0.0f, atan2(-right.x, -right.z), 0.0f);
            //calculate quaternion from euler angles
            XMVECTOR quat = XMQuaternionRotationRollPitchYaw(rot.x, rot.y, rot.z);
            XMFLOAT4 quat_f;
            XMStoreFloat4(&quat_f, quat);
            //set parent rotation
            Transform::RotateToQuat(parent->GetTransform(),quat_f);
            rigidBody->SetGlobalRotation(quat_f);
        }

        //jump
        if (Input::GetKeyTrigger(VK_SPACE))
        {
            XMFLOAT3 velocity = rigidBody->GetLinearVelocity();
            rigidBody->SetLinearVelocity(XMFLOAT3(velocity.x, velocity.y + 10.0f, velocity.z));
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
            forward = XMFLOAT3(-forward.x * 10.0f, forward.y * 10.0f, -forward.z * 10.0f);
            bullet->SetVelocity(forward);
            XMFLOAT3 bullet_pos = parent_pos;
            bullet_pos.y += 1.0f;
            bullet->SetPosition(bullet_pos);
            bullet->QueueSpawn();
        }
    }

    //Get Terrain
    CTerrain* terrain = Manager::FindEntityByName("Terrain")->GetComponent<CTerrain>();
    //Get Height
    if(terrain == nullptr)
    {
        parent->Unlock();
        return;
    }
    /*XMFLOAT3 parent_pos = parent->GetTransform()->position;
    float height = terrain->GetHeight(parent_pos);
    //Set parent y position to terrain height
    //set height in rigidbody
    CPhysXRigidBody* rigidBody = parent->GetComponent<CPhysXRigidBody>();
    rigidBody->GetActor()->is<physx::PxRigidDynamic>()->setKinematicTarget(physx::PxTransform(parent_pos.x, height, parent_pos.z));*/

    //animation
    CAnimationModel* animModel = parent->GetComponent<CAnimationModel>();
    if(animModel)
    {
        //get velocity
        XMFLOAT3 velocity = parent->GetComponent<CPhysXRigidBody>()->GetLinearVelocity();
        float speed = sqrt(velocity.x * velocity.x + velocity.z * velocity.z);
        animModel->Update("Idle", animation_frame_, "Run", animation_frame_, speed / 9.0f);
        animation_frame_ += forward_;
    }
    parent->Unlock();
}
