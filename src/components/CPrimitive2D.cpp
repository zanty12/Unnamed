#include "CPrimitive2D.h"

void CPrimitive2D::CleanUp()
{
    if(vertex_buffer_)
        vertex_buffer_->Release();
    if(vertex_shader_)
        vertex_shader_->Release();
    if(pixel_shader_)
        pixel_shader_->Release();
    if(vertex_layout_)
        vertex_layout_->Release();
}
