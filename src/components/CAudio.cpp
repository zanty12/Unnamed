#include "main.h"
#include "CAudio.h"

IXAudio2* CAudio::m_Xaudio = NULL;
IXAudio2MasteringVoice* CAudio::m_MasteringVoice = NULL;


void CAudio::StartMaster()
{
    // COM初期化
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    // XAudio生成
    XAudio2Create(&m_Xaudio, 0);

    // マスタリングボイス生成
    m_Xaudio->CreateMasteringVoice(&m_MasteringVoice);
}


void CAudio::CleanUpMaster()
{
    m_MasteringVoice->DestroyVoice();
    m_Xaudio->Release();
    CoUninitialize();
}


void CAudio::Load(const char* FileName)
{
    // サウンドデータ読込
    WAVEFORMATEX wfx = {0};

    {
        HMMIO hmmio = NULL;
        MMIOINFO mmioinfo = {0};
        MMCKINFO riffchunkinfo = {0};
        MMCKINFO datachunkinfo = {0};
        MMCKINFO mmckinfo = {0};
        UINT32 buflen;
        LONG readlen;


        hmmio = mmioOpen((LPSTR)FileName, &mmioinfo, MMIO_READ);
        assert(hmmio);

        riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
        mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

        mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
        mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

        if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
        {
            mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
        }
        else
        {
            PCMWAVEFORMAT pcmwf = {0};
            mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
            memset(&wfx, 0x00, sizeof(wfx));
            memcpy(&wfx, &pcmwf, sizeof(pcmwf));
            wfx.cbSize = 0;
        }
        mmioAscend(hmmio, &mmckinfo, 0);

        datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
        mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);


        buflen = datachunkinfo.cksize;
        sound_data_ = new unsigned char[buflen];
        readlen = mmioRead(hmmio, (HPSTR)sound_data_, buflen);


        length_ = readlen;
        play_length_ = readlen / wfx.nBlockAlign;


        mmioClose(hmmio, 0);
    }


    // サウンドソース生成
    m_Xaudio->CreateSourceVoice(&source_voice_, &wfx);
    assert(source_voice_);
}


void CAudio::CleanUp()
{
    source_voice_->Stop();
    source_voice_->DestroyVoice();

    delete[] sound_data_;
}


void CAudio::Play(bool Loop)
{
    source_voice_->Stop();
    source_voice_->FlushSourceBuffers();


    // バッファ設定
    XAUDIO2_BUFFER bufinfo;

    memset(&bufinfo, 0x00, sizeof(bufinfo));
    bufinfo.AudioBytes = length_;
    bufinfo.pAudioData = sound_data_;
    bufinfo.PlayBegin = 0;
    bufinfo.PlayLength = play_length_;

    // ループ設定
    if (Loop)
    {
        bufinfo.LoopBegin = 0;
        bufinfo.LoopLength = play_length_;
        bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
    }

    source_voice_->SubmitSourceBuffer(&bufinfo, NULL);

    /*
        float outputMatrix[4] = { 0.0f , 0.0f, 1.0f , 0.0f };
        m_SourceVoice->SetOutputMatrix(m_MasteringVoice, 2, 2, outputMatrix);
        //m_SourceVoice->SetVolume(0.1f);
    */


    // 再生
    source_voice_->Start();
}

void CAudio::Stop()
{
    source_voice_->Stop();
}

void CAudio::SetVolume(float Volume)
{
    source_voice_->SetVolume(Volume);
}
