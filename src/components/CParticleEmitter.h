#pragma once
#include "main.h"
#include "renderer.h"
#include "Component.h"
#include "traits/drawable.h"

class CParticleEmitter : public Component,public Drawable
{
private:
    ID3D11Buffer* vertex_buffer_{};
    ID3D11ShaderResourceView* m_Texture{};

    ID3D11VertexShader* vertex_shader_{};
    ID3D11PixelShader* pixel_shader_{};
    ID3D11InputLayout* vertex_layout_{};

    int m_Count{};

    struct PARTICLE
    {
        bool Enable;
        int Life;
        XMFLOAT3 Position;
        XMFLOAT3 Scale;
        XMFLOAT3 Velocity;
        XMFLOAT4 Color;
    };
    static const int PARTICLE_MAX = 70000;
    PARTICLE m_Particle[ PARTICLE_MAX] {};

public:
    CParticleEmitter() : Component("ParticleEmitter"),Drawable(2){};
    void Start() override;
    void CleanUp() override;
    void Update()override;
    void Draw() override;
};