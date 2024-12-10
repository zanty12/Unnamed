#pragma once
#include <DirectXMath.h>
#include "system/PhysX_Impl.h"
using namespace DirectX;

//Technically a component but it is treated as a helper class
//use as struct to reduce memory allocations
struct Transform
{
public:
    XMFLOAT3 position;
    XMFLOAT3 scale;
    XMFLOAT4 quaternion{0.0f, 0.0f, 0.0f, 1.0f};

    static Transform Identity()
    {
        return Transform{XMFLOAT3{0.0f, 0.0f, 0.0f}, XMFLOAT3{1.0f, 1.0f, 1.0f}, XMFLOAT4{0.0f, 0.0f, 0.0f, 1.0f}};
    }

    static void MoveTo(Transform& transform, XMFLOAT3 position)
    {
        transform.position = position;
    }

    static void RotateTo(Transform& transform, XMFLOAT3 rotation)
    {
        //convert rotation to quaternion
        RotateToQuat(transform, EulerToQuat(rotation));
    }

    static void RotateToQuat(Transform& transform, XMFLOAT4 quat)
    {
        transform.quaternion = quat;
    }

    static void ScaleTo(Transform& transform, XMFLOAT3 scale)
    {
        transform.scale = scale;
    }

    static void MoveBy(Transform& transform, XMFLOAT3 position)
    {
        transform.position.x += position.x;
        transform.position.y += position.y;
        transform.position.z += position.z;
    }

    static void RotateBy(Transform& transform, XMFLOAT3 rotation)
    {
        RotateToQuat(transform, EulerToQuat(rotation));
    }

    static void RotateByQuat(Transform& transform, XMFLOAT4 quat)
    {
        XMVECTOR quat1 = XMLoadFloat4(&transform.quaternion);
        XMVECTOR quat2 = XMLoadFloat4(&quat);
        XMVECTOR resultQuat = XMQuaternionMultiply(quat1, quat2);
        XMFLOAT4 result;
        XMStoreFloat4(&result, resultQuat);
        transform.quaternion = result;

    }

    static void ScaleBy(Transform& transform, XMFLOAT3 scale)
    {
        transform.scale.x *= scale.x;
        transform.scale.y *= scale.y;
        transform.scale.z *= scale.z;
    }

    static void Copy(Transform& transform, const Transform& other)
    {
        transform.position = other.position;
        transform.scale = other.scale;
        transform.quaternion = other.quaternion;
    }

    //return the forward vector of a transform
    static XMFLOAT3 GetForward(const Transform& transform)
    {
        //get rotation matrix from quaternion
        XMMATRIX rot = XMMatrixRotationQuaternion(XMLoadFloat4(&transform.quaternion));

        XMFLOAT3 forward;
        XMStoreFloat3(&forward, rot.r[2]);
        return forward;
    }

    // return the normalized right vector of a forward vector
    static XMFLOAT3 GetRight(XMFLOAT3 forward)
    {
        XMFLOAT3 right;
        XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);
        XMStoreFloat3(&right, XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&up), XMLoadFloat3(&forward))));
        return right;
    }

    // Function to rotate a point around another point
    static XMFLOAT3 RotatePointAroundTarget(const XMFLOAT3& point, const XMFLOAT3& targetpt, float anglerad,
                                            XMFLOAT3 axis = XMFLOAT3(0, 1, 0))
    {
        // Translate the coordinate system
        XMFLOAT3 translatedPoint;
        XMStoreFloat3(&translatedPoint, XMLoadFloat3(&point) - XMLoadFloat3(&targetpt));

        // Create a rotation matrix
        XMMATRIX rotationMatrix = XMMatrixRotationAxis(XMVectorSet(axis.x, axis.y, axis.z, 0.0f), anglerad);

        // Apply the rotation matrix
        XMFLOAT3 rotatedPoint;
        XMStoreFloat3(&rotatedPoint, XMVector3TransformCoord(XMLoadFloat3(&translatedPoint), rotationMatrix));

        // Translate back
        XMStoreFloat3(&rotatedPoint, XMLoadFloat3(&rotatedPoint) + XMLoadFloat3(&targetpt));

        return rotatedPoint;
    }

    static physx::PxTransform ToPhysXTransform(const Transform& transform)
    {
        physx::PxVec3 position = physx::PxVec3(transform.position.x, transform.position.y, transform.position.z);
        physx::PxQuat rotation = physx::PxQuat(transform.quaternion.x, transform.quaternion.y,
                                               transform.quaternion.z, transform.quaternion.w);
        return physx::PxTransform(position, rotation);
    }

    static Transform ToWorld(const Transform& parent,const Transform& local)
    {
        Transform world;
        world.position = parent.position;
        world.scale = parent.scale;
        world.quaternion = parent.quaternion;
        MoveBy(world, local.position);
        RotateByQuat(world, local.quaternion);
        ScaleBy(world, local.scale);
        return world;
    }

    static XMFLOAT4 EulerToQuat(XMFLOAT3 rotation)
    {
        XMFLOAT4 quat;
        XMVECTOR rotationVector = XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y,
                                                                   rotation.z);
        XMStoreFloat4(&quat, rotationVector);
        return quat;
    }

    static XMFLOAT3 QuatToEuler(XMFLOAT4 quaternion)
    {
        //calculate eular angles
        XMFLOAT3 angles;
        // roll (x-axis rotation)
        double sinr_cosp = 2 * (quaternion.w * quaternion.x + quaternion.y * quaternion.z);
        double cosr_cosp = 1 - 2 * (quaternion.x * quaternion.x + quaternion.y * quaternion.y);
        angles.x = static_cast<float>(std::atan2(sinr_cosp, cosr_cosp));

        // pitch (y-axis rotation)
        double sinp = std::sqrt(1 + 2 * (quaternion.w * quaternion.y - quaternion.x * quaternion.z));
        double cosp = std::sqrt(1 - 2 * (quaternion.w * quaternion.y - quaternion.x * quaternion.z));
        angles.y = 2.0f * static_cast<float>(std::atan2(sinp, cosp)) - XM_PI / 2;

        // yaw (z-axis rotation)
        double siny_cosp = 2 * (quaternion.w * quaternion.z + quaternion.x * quaternion.y);
        double cosy_cosp = 1 - 2 * (quaternion.y * quaternion.y + quaternion.z * quaternion.z);
        angles.z = static_cast<float>(std::atan2(siny_cosp, cosy_cosp));

        return angles;
    }
};
