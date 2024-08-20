
#include "manager.h"
#include "system/input.h"
#include "CMouseCursor.h"


void CMouseCursor::Update()
{
    //Get Mouse Position
    POINT mouse = Input::GetMousePos();
    //Get World Position of mouse
    CCamera* camera = Manager::GetActiveCamera();
    if(camera)
    {
        XMFLOAT4X4 view_matrix = camera->GetViewMatrix();
        XMFLOAT4X4 proj_matrix = camera->GetProjectionMatrix();
        XMMATRIX view = XMLoadFloat4x4(&view_matrix);
        XMMATRIX proj = XMLoadFloat4x4(&proj_matrix);
        //Get normalized vector from view position to mouse position
        XMVECTOR mouse_world_pos = Input::GetMouseWorldPos(view, proj);
        // Calculate the vector from the camera to the mouse position
        XMFLOAT3 camera_pos = camera->GetPosition();
        XMVECTOR camera_vec = XMLoadFloat3(&camera_pos);
        XMVECTOR vector_to_mouse = XMVectorSubtract(mouse_world_pos, camera_vec);

        // Calculate the length of the vector
        float length = XMVectorGetX(XMVector3Length(vector_to_mouse));

        // Define the maximum allowed length
        const float max_length = 20.0f; // Example limit

        // If the length exceeds the limit, normalize and scale the vector
        //Only limit the length if the vector is pointing upwards
        if (length > max_length && XMVectorGetY(vector_to_mouse) > 0)
        {
            vector_to_mouse = XMVector3Normalize(vector_to_mouse);
            vector_to_mouse = XMVectorScale(vector_to_mouse, max_length);
            mouse_world_pos = XMVectorAdd(camera_vec, vector_to_mouse);
        }

        if(XMVectorGetY(vector_to_mouse) < 0)
        {
            float y = XMVectorGetY(vector_to_mouse);
            float camera_y = XMVectorGetY(camera_vec);
            float length = 0.5f - camera_y;
            length = length / y;
            vector_to_mouse = XMVectorScale(vector_to_mouse, length);
            mouse_world_pos = XMVectorAdd(camera_vec, vector_to_mouse);
        }

        // Calculate the new mouse world position with the limited vector
        else
            mouse_world_pos = XMVectorAdd(camera_vec, vector_to_mouse);

        //Set the position of the entity to the mouse position
        Entity* parent = Manager::FindEntityByID(parent_id_);
        if(parent)
        {
            Transform* transform = parent->GetTransform();
            if(transform)
            {
                Transform::MoveTo(transform,XMFLOAT3(XMVectorGetX(mouse_world_pos), XMVectorGetY(mouse_world_pos), XMVectorGetZ(mouse_world_pos)));
            }
        }

    }
}