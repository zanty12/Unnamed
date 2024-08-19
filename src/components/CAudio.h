#pragma once
#include <xaudio2.h>
#include "component.h"

class CAudio : public Component
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*	source_voice_{};
	BYTE*					sound_data_{};

	int						length_{};
	int						play_length_{};


public:
	static void StartMaster();
	static void CleanUpMaster();

	CAudio() : Component("Audio"){};
	void Start() override{};
	void Update() override{};
	void CleanUp() override;

	void Load(const char *FileName);
	void Play(bool Loop = false);
	void Stop();
	void SetVolume(float Volume);


};

