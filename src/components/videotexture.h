#pragma once
#include "../main.h"
#include "../renderer.h"
#include <iostream>
#include <list>

#include "component.h"
#include "../time.h"
#include "../include/video_reader.hpp"
#include "../imgui_impl_hal.h"
#include "texture.h"

struct frame_data
{
    int64_t ts;
    uint8_t* data;
};

class VideoTexture : public Texture
{
private:
    //directx
    VideoReaderState vr_state_;
    ID3D11Texture2D* texture_;
    ID3D11ShaderResourceView* texture_view_;

    //setting
    std::string filename_;
    XMFLOAT2 debug_window_size_ = XMFLOAT2(100.0f,100.0f);
    XMFLOAT2 debug_window_pos_ = XMFLOAT2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    bool loop_ = false;

    //video playback control
    uint8_t* frame_data_;
    bool first_frame_ = true;
    double time_ = 0.0;
    std::list<frame_data> frame_buffer_;
    int64_t end_pts_ = 0;
    double pts_ = 0;
    bool loaded_ = false;
    int64_t first_frame_pts_ = 0;


public:
    VideoTexture(const char* filename) : Texture("VideoPlayer"),filename_(filename){}

    void Start() override
    {
        if (!video_reader_open(&vr_state_, filename_.c_str()))
        {
            std::cout << "Couldn't open video file (make sure you set a video file that exists)\n";
        }

        // Create a DirectX11 texture
        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.Width = vr_state_.width;
        desc.Height = vr_state_.height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        Renderer::GetDevice()->CreateTexture2D(&desc, NULL, &texture_);

        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;
        Renderer::GetDevice()->CreateShaderResourceView(texture_, &srvDesc, &texture_view_);

        // Allocate frame buffer
        constexpr int ALIGNMENT = 128;
        const int frame_width = vr_state_.width;
        const int frame_height = vr_state_.height;
        frame_data_ = (uint8_t*)_aligned_malloc(frame_width * frame_height * 4, ALIGNMENT);
        if (frame_data_ == 0)
        {
            std::cout << "Couldn't allocate frame buffer\n";
        }

        debug_window_size_ = XMFLOAT2(frame_width, frame_height);
    };
    void CleanUp() override
    {
        _aligned_free(frame_data_);
        for (auto frame : frame_buffer_)
        {
            _aligned_free(frame.data);
        }
        video_reader_close(&vr_state_);
        texture_->Release();
    };

    ~VideoTexture() override = default;

    void Update() override
    {
        time_ += Time::GetDeltaTime();

        // Define a constant for the maximum buffer size.
        const int MAX_BUFFER_SIZE = 10; // Change this value as needed.

        int64_t pts = 0;
        // Check if the buffer is not full before loading frame data.
        if (!loaded_ && frame_buffer_.size() < MAX_BUFFER_SIZE)
        {
            if (!video_reader_read_frame(&vr_state_, frame_data_, &pts))
            {
                std::cout << "Couldn't load video frame\n";
                return;
            }
            //buffer frame
            frame_data frame;
            frame.ts = pts;
            frame.data = (uint8_t*)_aligned_malloc(vr_state_.width * vr_state_.height * 4, 128);
            memcpy(frame.data, frame_data_, vr_state_.width * vr_state_.height * 4);
            frame_buffer_.push_back(frame);
            if (first_frame_)
            {
                first_frame_ = false;
                first_frame_pts_ = pts;
            }
            if (pts == end_pts_ && !loaded_ && end_pts_ != 0)
            {
                loaded_ = true;
            }
            //count max pts
            if (pts > end_pts_)
            {
                end_pts_ = pts;
            }
        }
        //loop back if at end of video
        if (loop_ && loaded_ && end_pts_ != 0 && frame_buffer_.size() == 0)
        {
            loaded_ = false;
            //int64_t start = vr_state_.av_format_ctx->streams[vr_state_.video_stream_index-1]->start_time;
            video_reader_seek_frame(&vr_state_, first_frame_pts_);
            time_ = 0.0;
        }

        //load next frame
        if (frame_buffer_.size() > 0 && time_ > frame_buffer_.begin()->ts * (double)vr_state_.time_base.num / (double)
            vr_state_.time_base.den)
        {
            frame_data frame = *frame_buffer_.begin();
            memcpy(frame_data_, frame.data, vr_state_.width * vr_state_.height * 4);
            pts_ = frame.ts;
            //load frame data to texture
            D3D11_MAPPED_SUBRESOURCE resource;
            Renderer::GetDeviceContext()->Map(texture_, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
            uint8_t* dest = (uint8_t*)resource.pData;
            for (int y = 0; y < vr_state_.height; ++y)
            {
                memcpy(dest, frame_data_ + y * vr_state_.width * 4, vr_state_.width * 4);
                dest += resource.RowPitch;
            }
            Renderer::GetDeviceContext()->Unmap(texture_, 0);

            D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
            ZeroMemory(&srvDesc, sizeof(srvDesc));
            srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            srvDesc.Texture2D.MipLevels = 1;
            srvDesc.Texture2D.MostDetailedMip = 0;
            Renderer::GetDevice()->CreateShaderResourceView(texture_, &srvDesc, &texture_view_);
            // Remove the consumed frame from the buffer.
            _aligned_free(frame.data);
            frame_buffer_.pop_front();
        }
    }

    void DebugDraw() const
    {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        bool open = true;
        ImGui::SetNextWindowPos(ImVec2(debug_window_pos_.x - debug_window_size_.x  / 2, debug_window_pos_.y - debug_window_size_.y  / 2));
        // Draw the texture with ImGui
        ImGui::Begin(filename_.c_str(), &open, window_flags);
        //ImGui::Text("time: %.2f, pts: %.2f", time_, pts_);
        ImGui::Image((void*)texture_view_, ImVec2(debug_window_size_.x , debug_window_size_.y ));
        ImGui::End();
    }

    ID3D11ShaderResourceView* GetView() override
    {
        return texture_view_;
    }

    void SetLoop(bool loop)
    {
        loop_ = loop;
    }

    void SetSize(XMFLOAT2 size)
    {
        debug_window_size_ = size;
    }

    void SetWindowPos(XMFLOAT2 pos)
    {
        debug_window_pos_ = pos;
    }
};
