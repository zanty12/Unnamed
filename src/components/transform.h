﻿#pragma once
#include <DirectXMath.h>
#include "system/PhysX_Impl.h"
using namespace DirectX;

//Technically a component but it is treated as a helper class
struct Transform
{
public:
    XMFLOAT3 position;
    XMFLOAT3 rotation;
    XMFLOAT3 scale;
    XMFLOAT4 quaternion{0.0f, 0.0f, 0.0f, 1.0f};

    bool quaternion_set = false;

    static Transform Identity()
    {
        return Transform{XMFLOAT3{0.0f, 0.0f, 0.0f}, XMFLOAT3{0.0f, 0.0f, 0.0f}, XMFLOAT3{1.0f, 1.0f, 1.0f}};
    }

    static Transform* MoveTo(Transform* transform, XMFLOAT3 position)
    {
        transform->position = position;
        return transform;
    }

    static Transform* RotateTo(Transform* transform, XMFLOAT3 rotation)
    {
        transform->rotation = rotation;
        EulerToQuat(transform);
        return transform;
    }

    static Transform* RotateToQuat(Transform* transform, XMFLOAT4 quat)
    {
        transform->quaternion = quat;
        QuatToEuler(transform);
        return transform;
    }

    static Transform* ScaleTo(Transform* transform, XMFLOAT3 scale)
    {
        transform->scale = scale;
        return transform;
    }

    static Transform* MoveBy(Transform* transform, XMFLOAT3 position)
    {
        transform->position.x += position.x;
        transform->position.y += position.y;
        transform->position.z += position.z;
        return transform;
    }

    static Transform* RotateBy(Transform* transform, XMFLOAT3 rotation)
    {
        transform->rotation.x += rotation.x;
        transform->rotation.y += rotation.y;
        transform->rotation.z += rotation.z;
        EulerToQuat(transform);
        return transform;
    }

    static Transform* RotateByQuat(Transform* transform, XMFLOAT4 quat)
    {
        transform->quaternion.x += quat.x;
        transform->quaternion.y += quat.y;
        transform->quaternion.z += quat.z;
        transform->quaternion.w += quat.w;
        QuatToEuler(transform);
        return transform;
    }

    static Transform* ScaleBy(Transform* transform, XMFLOAT3 scale)
    {
        transform->scale.x *= scale.x;
        transform->scale.y *= scale.y;
        transform->scale.z *= scale.z;
        return transform;
    }

    static Transform* Copy(Transform* transform, const Transform* other)
    {
        transform->position = other->position;
        transform->rotation = other->rotation;
        transform->scale = other->scale;
        transform->quaternion = other->quaternion;
        transform->quaternion_set = other->quaternion_set;
        return transform;
    }

    //return the forward vector of a transform
    static XMFLOAT3 GetForward(Transform* transform)
    {
        XMMATRIX rot =
            XMMatrixRotationRollPitchYaw(transform->rotation.x, transform->rotation.y, transform->rotation.z);

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

    static void SetQuaternionMode(Transform* transform, bool mode)
    {
        transform->quaternion_set = mode;
    }

    static physx::PxTransform ToPhysXTransform(Transform* transform)
    {
        physx::PxVec3 position = physx::PxVec3(transform->position.x, transform->position.y, transform->position.z);
        physx::PxQuat rotation = physx::PxQuat(transform->quaternion.x, transform->quaternion.y,
                                               transform->quaternion.z, transform->quaternion.w);
        return physx::PxTransform(position, rotation);
    }

private:
    static void EulerToQuat(Transform* transform)
    {
        XMVECTOR rotationVector = XMQuaternionRotationRollPitchYaw(transform->rotation.x, transform->rotation.y,
                                                                   transform->rotation.z);
        XMStoreFloat4(&transform->quaternion, rotationVector);
        transform->quaternion_set = true;
    }

    static void QuatToEuler(Transform* transform)
    {
        XMVECTOR quaternion = XMLoadFloat4(&transform->quaternion);
        XMVECTOR euler = XMQuaternionRotationRollPitchYawFromVector(quaternion);
        XMStoreFloat3(&transform->rotation, euler);
    }
};