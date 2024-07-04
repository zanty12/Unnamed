#pragma once
#include "../main.h"
#include "../renderer.h"

#include "CTexture.h"
#include "manager.h"
#include "timesystem.h"
#include "textureLoader.h"

class CSprite2D : public CTexture
{
private:
    std::wstring texture_path_ = L"asset\\texture\\explosion.png";
    ID3D11Texture2D* texture_resource_ = NULL;
    int width_ = 1;
    int height_ = 1;
    bool loop_ = false;
    int fps_ = 24;
    float frame_time_ = 0.0f;
    float start_u_ = 0.0f;
    float start_v_ = 0.0f;
    float end_u_ = 1.0f;
    float end_v_ = 1.0f;

public:
    CSprite2D() = default;

    CSprite2D(const std::wstring& path) :  texture_path_(path)
    {
    }

    ~CSprite2D() override = default;

    void Start() override
    {
        //Texture
        texture_resource_ = TextureLoader::LoadTexture(texture_path_);
        assert(texture_resource_);
        end_u_ = 1.0f / static_cast<float>(width_);
        end_v_ = 1.0f / static_cast<float>(height_);
    }

    void Update() override
    {
        //update frame time
        frame_time_ += Time::GetDeltaTime();
        if (frame_time_ >= 1.0f / static_cast<float>(fps_))
        {
            frame_time_ = 0.0f;
            start_u_ += 1.0f / static_cast<float>(width_);
            end_u_ = start_u_ + 1.0f / static_cast<float>(width_);
            if (start_u_ >= 1.0f)
            {
                start_u_ = 0.0f;
                end_u_ = 1.0f / static_cast<float>(width_);
                start_v_ += 1.0f / static_cast<float>(height_);
                end_v_ = start_v_ + 1.0f / static_cast<float>(height_);
                if (start_v_ >= 1.0f)
                {
                    if (loop_)
                    {
                        start_v_ = 0.0f;
                        end_v_ = 1.0f / static_cast<float>(height_);
                    }
                    else
                    {
                        //remove entity
                        Manager::QueueForRemoval(parent_id_);
                    }
                }
            }
        }
    }

    void CleanUp() override
    {
        texture_resource_->Release();
    }

    ID3D11ShaderResourceView* GetView()
    {
        ID3D11ShaderResourceView* view = nullptr;
        HRESULT hr = Renderer::GetDevice()->CreateShaderResourceView(texture_resource_, nullptr, &view);
        if (FAILED(hr)) return nullptr;
        return view;
    }

    void SetTexturePath(const std::wstring& path) { texture_path_ = path; }

    XMFLOAT2 GetStartUV() { return XMFLOAT2(start_u_, start_v_); }
    XMFLOAT2 GetEndUV() { return XMFLOAT2(end_u_, end_v_); }
    void SetWidth(int width) { width_ = width; }
    void SetHeight(int height) { height_ = height; }
    void SetLoop(bool loop) { loop_ = loop; }
    void SetFPS(int fps) { fps_ = fps; }
};
