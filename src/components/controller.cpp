#include "main.h"
#include "input.h"
#include "controller.h"
#include "entity.h"



void Controller::Update(Entity* parent)
{
    //move parent with keyboard input
    if (Input::GetKeyPress('W'))
    {
        Transform::MoveBy(parent->GetTransform(), DirectX::XMFLOAT3(0.0f, 0.0f, 0.1f));
    }
    if (Input::GetKeyPress('S'))
    {
        Transform::MoveBy(parent->GetTransform(), DirectX::XMFLOAT3(0.0f, 0.0f, -0.1f));
    }
    if (Input::GetKeyPress('A'))
    {
        Transform::MoveBy(parent->GetTransform(), DirectX::XMFLOAT3(-0.1f, 0.0f, 0.0f));
    }
    if (Input::GetKeyPress('D'))
    {
        Transform::MoveBy(parent->GetTransform(), DirectX::XMFLOAT3(0.1f, 0.0f, 0.0f));
    }
}
