#include "../Engine/Windows.h"

#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

HWND hWnd;
HWND GetWindowHandle() { return hWnd; }

LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	switch (message_id)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window_handle, message_id, wparam, lparam);
		break;
	}

	return 0;
}

bool MakeWindow(int width, int height, const char* title)
{
	WNDCLASSEX window_class = {
		sizeof(WNDCLASSEXA),			// �\���̂̃T�C�Y
		CS_HREDRAW | CS_VREDRAW,		// �N���X�̃X�^�C��
		WindowProc,						// �E�B���h�E�v���V�[�W��
		0,								// �⏕������
		0,								// �⏕������
		GetModuleHandle(nullptr),		// ���̃v���O�����̃C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION),// �A�C�R���摜
		LoadCursor(NULL, IDC_HAND),	// �J�[�\���摜
		NULL,							// �w�i�u���V(�w�i�F)
		NULL,							// ���j���[��
		WINDOW_CLASS_NAME,				// �N���X��									
		NULL							// �������A�C�R��
	};

	// �\���̂̓o�^
	if (RegisterClassEx(&window_class) == 0)
	{
		return 0;
	}

	// �E�B���h�E�쐬
	hWnd = CreateWindowA(
		WINDOW_CLASS_NAME,
		title,
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE | WS_MAXIMIZE,
		CW_USEDEFAULT,
		0,
		width,
		height,
		NULL,
		NULL,
		GetModuleHandle(nullptr),
		NULL);


	//�t���X�N���[�����[�h�ɂȂ�
	//SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);


	ShowWindow(hWnd, SW_SHOW);

	UpdateWindow(hWnd);


	return hWnd;
}
