#pragma once
#include <d3d11.h>

#include "../entity.h"

class Player
{
private:
    Entity* entity_ = nullptr;

    ID3D11VertexShader* vertex_shader_ = nullptr;
    ID3D11PixelShader* pixel_shader_ = nullptr;
    ID3D11InputLayout* vertex_layout_ = nullptr;
public:
    Player() = default;
    ~Player();
    void Start();
    void Update();
    void Draw();
};
