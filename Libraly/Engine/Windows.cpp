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
		sizeof(WNDCLASSEXA),			// 構造体のサイズ
		CS_HREDRAW | CS_VREDRAW,		// クラスのスタイル
		WindowProc,						// ウィンドウプロシージャ
		0,								// 補助メモリ
		0,								// 補助メモリ
		GetModuleHandle(nullptr),		// このプログラムのインスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),// アイコン画像
		LoadCursor(NULL, IDC_HAND),	// カーソル画像
		NULL,							// 背景ブラシ(背景色)
		NULL,							// メニュー名
		WINDOW_CLASS_NAME,				// クラス名									
		NULL							// 小さいアイコン
	};

	// 構造体の登録
	if (RegisterClassEx(&window_class) == 0)
	{
		return 0;
	}

	// ウィンドウ作成
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


	//フルスクリーンモードになる
	//SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);


	ShowWindow(hWnd, SW_SHOW);

	UpdateWindow(hWnd);


	return hWnd;
}
