#pragma once
#include <DirectXMath.h>

struct Transform
{
public:
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 rotation;
    DirectX::XMFLOAT3 scale;
};
