#pragma once
#include "Component.h"

class CTexture : public Component
{
public:
    CTexture(std::string type) : Component(std::move(type)) {}
    virtual ~CTexture() = default;

    virtual ID3D11ShaderResourceView* GetView() = 0;
};
