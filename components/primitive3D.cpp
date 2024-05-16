#include "primitive3D.h"

void Primitive3D::CleanUp()
{
    vertex_buffer_->Release();
    texture_->Release();
    vertex_shader_->Release();
    pixel_shader_->Release();
    vertex_layout_->Release();
}
