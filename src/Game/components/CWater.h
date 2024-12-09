#pragma once
#include "components/CTexture.h"
#include "renderer.h"
#include "components/Component.h"
#include "system/PhysX_Impl.h"
#include "traits/drawable.h"

class CWater : public Component, public Drawable
{
    //directx
    ID3D11Buffer* vertex_buffer_{};
	ID3D11Buffer* index_buffer_{};
    ID3D11VertexShader* vertex_shader_{};
    ID3D11PixelShader* pixel_shader_{};
    ID3D11InputLayout* vertex_layout_{};

    // Data
    std::string vertex_shader_path_ = "asset\\shader\\unlitTextureVS.cso";
    std::string pixel_shader_path_= "asset\\shader\\unlitTexturePS.cso";
    CTexture* texture_ = nullptr;
    XMFLOAT2 start_uv_ = XMFLOAT2(0.0f, 0.0f);
    XMFLOAT2 end_uv_ = XMFLOAT2(1.0f, 1.0f);
    VERTEX_3D* vertex_{};
	std::vector<physx::PxVec3> physX_vertex_;
	std::vector<physx::PxU32> physX_index_;
	unsigned int* index_;

    physx::PxRigidStatic* actor_{};
    physx::PxShape* shape_;

    int div_x_ = 20;
    int div_z_ = 20;


public:
    CWater(): Component("Water",DrawCallers),Drawable(2){}
    void Start() override;
    void Update() override;
    void Draw() override;
    void CleanUp() override;
	void SetTexture(CTexture* texture) { texture_ = texture; }
	void SetEndUV(XMFLOAT2 end_uv) { end_uv_ = end_uv; }
	void SetStartUV(XMFLOAT2 start_uv) { start_uv_ = start_uv; }
    void SetDivX(int div_x) { div_x_ = div_x; }
    void SetDivZ(int div_z) { div_z_ = div_z; }
	float GetHeight(XMFLOAT3 position);
};

