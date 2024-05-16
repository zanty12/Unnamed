#include "controller.h"
#include "entity.h"
#include "main.h"

void Controller::Update(Entity* parent)
{
    //move parent with keyboard input
    if (GetAsyncKeyState('W') & 0x8000)
    {
        Transform::MoveBy(parent->GetTransform(), DirectX::XMFLOAT3(0.0f, 0.0f, 0.1f));
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        Transform::MoveBy(parent->GetTransform(), DirectX::XMFLOAT3(0.0f, 0.0f, -0.1f));
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        Transform::MoveBy(parent->GetTransform(), DirectX::XMFLOAT3(-0.1f, 0.0f, 0.0f));
    }
    if (GetAsyncKeyState('D') & 0x8000)
    {
        Transform::MoveBy(parent->GetTransform(), DirectX::XMFLOAT3(0.1f, 0.0f, 0.0f));
    }
}
