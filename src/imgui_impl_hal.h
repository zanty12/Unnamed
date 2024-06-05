#pragma once

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

class ImGui_Hal
{
public:
	static void Start(void);
	static void Cleanup(void);
	static void BeginDraw(void);
	static void EndDraw(void);

};
