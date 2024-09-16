#include "CDirectXTKSphere.h"

#include "renderer.h"

void CDirectXTKSphere::Start()
{
    primitive_ = GeometricPrimitive::CreateSphere(Renderer::GetDeviceContext(), radius_, 16);
}

void CDirectXTKSphere::CleanUp()
{
    primitive_.release();
}