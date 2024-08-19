#pragma once

enum MouseButton
{
	LEFT_BUTTON,
	RIGHT_BUTTON,
	MIDDLE_BUTTON
};

class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
	static POINT m_MousePos;
	static POINT m_OldMousePos;
	static bool m_MouseButtonState[3];
	static bool m_OldMouseButtonState[3];

public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );
	static POINT GetMousePos();
	static XMVECTOR GetMouseWorldPos(XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	static bool GetMouseButtonPress(MouseButton button);
	static bool GetMouseButtonClick(MouseButton button);

private:
	static XMFLOAT2 ConvertScreenToNDC(XMFLOAT2 screenPos, int screenWidth, int screenHeight);
	static XMVECTOR ConvertNDCToWorld(DirectX::XMFLOAT2 ndc, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix);
};
