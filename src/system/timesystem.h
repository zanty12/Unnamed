#pragma once
#include <windows.h>
#pragma comment(lib, "winmm.lib")
class Time {
private:
	static DWORD startTime;
	static DWORD previousTime;
	static DWORD currentTime;
	static DWORD deltaTime;

public:

	static void Start(void);
	static void CleanUp(void);
	static void Update(void);
	static float GetDeltaTime(void);
	static float GetDeltaTime(float start);
	static float GetCurrentTime(void);
};