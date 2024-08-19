
#include "main.h"
#include "input.h"


BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];
POINT Input::m_MousePos;
POINT Input::m_OldMousePos;
bool Input::m_MouseButtonState[3];
bool Input::m_OldMouseButtonState[3];


void Input::Init()
{

	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );
	memset(m_MouseButtonState, 0, 3);
	memset(m_OldMouseButtonState, 0, 3);
}

void Input::Uninit()
{


}

void Input::Update()
{

	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );

	memcpy(m_OldMouseButtonState, m_MouseButtonState, 3);
	m_MouseButtonState[LEFT_BUTTON] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
	m_MouseButtonState[RIGHT_BUTTON] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
	m_MouseButtonState[MIDDLE_BUTTON] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;

	m_OldMousePos = m_MousePos;
	m_MousePos = GetMousePos();

}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

POINT Input::GetMousePos()
{
	HWND hwnd = GetWindow();
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(hwnd, &mousePos);
	return mousePos;
}

XMVECTOR Input::GetMouseWorldPos(XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	XMFLOAT2 mousepos = XMFLOAT2(static_cast<float>(m_MousePos.x), static_cast<float>(m_MousePos.y));
	XMFLOAT2 ndc = ConvertScreenToNDC(mousepos, SCREEN_WIDTH, SCREEN_HEIGHT);
	return ConvertNDCToWorld(ndc, viewMatrix, projectionMatrix);
}

DirectX::XMVECTOR Input::ConvertNDCToWorld(DirectX::XMFLOAT2 ndc, DirectX::XMMATRIX viewMatrix,
                                           DirectX::XMMATRIX projectionMatrix)
{
	DirectX::XMMATRIX invViewProj = DirectX::XMMatrixInverse(nullptr, viewMatrix * projectionMatrix);

	DirectX::XMVECTOR ndcPos = DirectX::XMVectorSet(ndc.x, ndc.y, 1.0f, 1.0f);
	DirectX::XMVECTOR worldPos = DirectX::XMVector3TransformCoord(ndcPos, invViewProj);

	return worldPos;
}

bool Input::GetMouseButtonPress(MouseButton button)
{
	return m_MouseButtonState[button];
}

bool Input::GetMouseButtonClick(MouseButton button)
{
	return m_MouseButtonState[button] && !m_OldMouseButtonState[button];
}

DirectX::XMFLOAT2 Input::ConvertScreenToNDC(XMFLOAT2 screenPos, int screenWidth, int screenHeight)
{
	DirectX::XMFLOAT2 ndc;
	ndc.x = (2.0f * screenPos.x) / screenWidth - 1.0f;
	ndc.y = 1.0f - (2.0f * screenPos.y) / screenHeight;
	return ndc;
}
