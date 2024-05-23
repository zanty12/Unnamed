#pragma once
#include <DirectXMath.h>

struct Transform
{
public:
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 rotation;
    DirectX::XMFLOAT3 scale;

    static Transform Identity()
    {
        return Transform{DirectX::XMFLOAT3{0.0f, 0.0f, 0.0f}, DirectX::XMFLOAT3{0.0f, 0.0f, 0.0f}, DirectX::XMFLOAT3{1.0f, 1.0f, 1.0f}};
    }

    static Transform* MoveTo(Transform* transform, DirectX::XMFLOAT3 position)
    {
        transform->position = position;
        return transform;
    }

    static Transform* RotateTo(Transform* transform, DirectX::XMFLOAT3 rotation)
    {
        transform->rotation = rotation;
        return transform;
    }

    static Transform* ScaleTo(Transform* transform, DirectX::XMFLOAT3 scale)
    {
        transform->scale = scale;
        return transform;
    }

    static Transform* MoveBy(Transform* transform, DirectX::XMFLOAT3 position)
    {
        transform->position.x += position.x;
        transform->position.y += position.y;
        transform->position.z += position.z;
        return transform;
    }

    static Transform* RotateBy(Transform* transform, DirectX::XMFLOAT3 rotation)
    {
        transform->rotation.x += rotation.x;
        transform->rotation.y += rotation.y;
        transform->rotation.z += rotation.z;
        return transform;
    }

    static Transform* ScaleBy(Transform* transform, DirectX::XMFLOAT3 scale)
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
        return transform;
    }
};
