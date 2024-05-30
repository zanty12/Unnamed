#pragma once
#include "component.h"

class Texture : public Component
{
public:
    Texture(std::string type) : Component(std::move(type)) {}
    virtual ~Texture() = default;

    virtual ID3D11ShaderResourceView* GetView() = 0;
};
