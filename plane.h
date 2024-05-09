#pragma once
#include <d3d11.h>

#include "transform.h"

class Plane
{
private:
    Transform transform_ = Transform::Identity();
    ID3D11Buffer* vertex_buffer_{};
    ID3D11ShaderResourceView* texture_{};

    ID3D11VertexShader* vertex_shader_{};
    ID3D11PixelShader* pixel_shader_{};
    ID3D11InputLayout* vertex_layout_{};
public:
    
};
