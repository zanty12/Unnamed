﻿#include "CPrimitive3D.h"

void CPrimitive3D::CleanUp()
{
    vertex_buffer_->Release();
    vertex_shader_->Release();
    pixel_shader_->Release();
    vertex_layout_->Release();
}
