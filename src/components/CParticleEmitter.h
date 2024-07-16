#pragma once
#include "main.h"
#include "renderer.h"
#include "Component.h"
#include "traits/drawable.h"

class CParticleEmitter : public Component,public Drawable
{
public:

};

class ParticleEmitter
{
private:
    ID3D11Buffer* m_VertexBuffer{};
    ID3D11ShaderResourceView* m_Texture{};

    ID3D11VertexShader* m_VertexShader{};
    ID3D11PixelShader* m_PixelShader{};
    ID3D11InputLayout* m_VertexLayout{};

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
    void Init();
    void Uninit();
    void Update();
    void Draw();
};