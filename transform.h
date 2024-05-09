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

    static Transform MoveTo(Transform transform, DirectX::XMFLOAT3 position)
    {
        transform.position = position;
        return transform;
    }

    static Transform RotateTo(Transform transform, DirectX::XMFLOAT3 rotation)
    {
        transform.rotation = rotation;
        return transform;
    }

    static Transform ScaleTo(Transform transform, DirectX::XMFLOAT3 scale)
    {
        transform.scale = scale;
        return transform;
    }
};
