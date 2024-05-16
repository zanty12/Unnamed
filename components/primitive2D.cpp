#include "primitive2D.h"

void Primitive2D::CleanUp()
{
    vertex_buffer_->Release();
    texture_->Release();
    vertex_shader_->Release();
    pixel_shader_->Release();
    vertex_layout_->Release();
}
