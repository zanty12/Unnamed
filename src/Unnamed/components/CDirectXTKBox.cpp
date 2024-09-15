#include "CDirectXTKBox.h"
#include "renderer.h"


void CDirectXTKBox::Start()
{
    primitive_ = GeometricPrimitive::CreateBox(Renderer::GetDeviceContext(), size_, false);
}

void CDirectXTKBox::CleanUp()
{
    primitive_.release();
}
