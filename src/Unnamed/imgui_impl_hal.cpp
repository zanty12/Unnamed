/**
 * @file ImGui_Hal.cpp
 * @brief DebugUI�N���X���������܂��B
 * @author Cheung To Hung
 * @date 2023/11/22
 */

#include "imgui_impl_hal.h"
#include "main.h"
#include "renderer.h"

 /**
  * @brief DebugUI�N���X�̃��\�b�h
  *
  * ���̃��\�b�h��ImGui�����������܂��B
  * ImGui�̃R���e�L�X�g��ݒ肵�AWin32��DirectX 11�p��ImGui�����������܂��B
  * �܂��A�X�^�C�����_�[�N�ɐݒ肵�A�t�@�C��������{��̃t�H���g��ǉ����܂��B
  */
void ImGui_Hal::Start()
{
	// ImGui�̃o�[�W�������`�F�b�N
	IMGUI_CHECKVERSION();
	// ImGui�̃R���e�L�X�g���쐬
	ImGui::CreateContext();
	// ImGui��IO���擾
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	// �E�B���h�E�n���h�����擾
	const HWND hWnd = GetWindow();
	// Win32�p��ImGui��������
	ImGui_ImplWin32_Init(hWnd);
	// DirectX 11�p��ImGui��������
	ImGui_ImplDX11_Init(Renderer::GetDevice(), Renderer::GetDeviceContext());

	// ImGui�̃X�^�C�����_�[�N�ɐݒ�
	ImGui::StyleColorsDark();
	// �t�@�C��������{��̃t�H���g��ǉ�
	io.Fonts->AddFontFromFileTTF("asset/fonts/NotoSansJP-Bold.ttf", 20.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	//io.Fonts->AddFontFromFileTTF("asset/TEXTURE/JF-Dot-Kappa20-0213.ttf", 135.0f, nullptr);
	// �}�E�X�J�[�\���̕`���L���ɂ���
	io.MouseDrawCursor = true;
}

/**
 * @brief ���̃��\�b�h��ImGui���g�p���Ă������\�[�X��������܂��B
 *
 * DirectX 11��Win32�p��ImGui���V���b�g�_�E�����AImGui�̃R���e�L�X�g��j�����܂��B
 */
void ImGui_Hal::Cleanup()
{
	// DirectX 11�p��ImGui���V���b�g�_�E��
	ImGui_ImplDX11_Shutdown();
	// Win32�p��ImGui���V���b�g�_�E��
	ImGui_ImplWin32_Shutdown();
	// ImGui�̃R���e�L�X�g��j��
	ImGui::DestroyContext();
}


/**
 * @brief ���̃��\�b�h��ImGui�̕`��v���Z�X���J�n���܂��B
 *
 * �V�����t���[���̂��߂�ImGui���������܂��B
 */
void ImGui_Hal::BeginDraw()
{
	// �V����DirectX 11�t���[���̂��߂�ImGui������
	ImGui_ImplDX11_NewFrame();
	// �V����Win32�t���[���̂��߂�ImGui������
	ImGui_ImplWin32_NewFrame();
	// �V����ImGui�t���[�����J�n
	ImGui::NewFrame();
}

/**
 * @brief ���̃��\�b�h��ImGui�̕`��v���Z�X���I�����܂��B
 *
 * DirectX 11���g�p����ImGui�̕`��f�[�^�������_�����O���܂��B
 */
void ImGui_Hal::EndDraw()
{
	// ImGui�̕`��f�[�^�������_�����O
	ImGui::Render();
	// DirectX 11���g�p����ImGui�̕`��f�[�^�������_�����O
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}