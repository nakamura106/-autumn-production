#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <D3dx9math.h>
#include "../Engine/Vec.h"
#include "../Engine/Windows.h"
#include "../Engine/Input.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

struct INPUTSTATE
{
	DWORD now;
	DWORD trg;
	DWORD ntrg;
};

static LPDIRECTINPUT8 g_InputInterface;		//!< DIRECTINPUT8のポインタ
static LPDIRECTINPUTDEVICE8 g_MouseDevice;		//!< DIRECTINPUTDEVICE8のポインタ
static LPDIRECTINPUTDEVICE8 g_GamePadDevice;
static ButtonState g_ButtonStates[ButtonKind::ButtonKindMax];
static DIMOUSESTATE g_PrevMouseState;			//!< マウスの１フレーム前の入力情報
static DIMOUSESTATE g_CurrentMouseState;		//!< マウスの現在の入力情報
static Vec2 g_MousePos;
static Vec2 g_MouseMoveVec;

// 入力インターフェースの作成
bool CreateInputInterface();

// マウスデバイスの作成
bool CreateMouseDevice();

// ゲームパッドデバイスの作成
bool CreateGamePadDevice();

// ゲームパッドの更新
void UpdateGamePad();

// マウスの更新
void UpdateMouse();

//ゲームパッドデバイスの作成-デバイス列挙の結果を受け取る構造体
struct DeviceEnumParameter
{
	LPDIRECTINPUTDEVICE8* GamePadDevice;
	int FindCount;
};

#define MOUSE_ON_VALUE (0x80)		// オン状態の値

static LPDIRECTINPUTDEVICE8 g_pKeyDevice;

// キー情報
static INPUTSTATE g_InputState;

BOOL SetUpCooperativeLevel(LPDIRECTINPUTDEVICE8 device)
{
	//協調モードの設定
	if (FAILED(device->SetCooperativeLevel(
		FindWindow(WINDOW_CLASS_NAME, nullptr),
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)
	))
	{
		return false;
	}
	return true;
}

BOOL StartGamePadControl()
{
	if (g_GamePadDevice == nullptr)
	{
		return false;
	}

	if (FAILED(g_GamePadDevice->Acquire()))
	{
		return false;
	}

	return true;
}

/*
	軸モード
		絶対値モード => 基準点からの位置
		相対値モード => 前回位置を基準とした位置

	DIPROPシリーズ
		DIPROPHEADER + プロパティ用のメンバ
	DIPROPWORD => DWORD型1つで済むプロパティを変更できる汎用構造体
*/
BOOL SetUpGamePadProperty(LPDIRECTINPUTDEVICE8 device)
{
	// 軸モードを絶対値モードとして設定
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	// ここからDIPROPのヘッダーにステータス設定
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;
	if (FAILED(device->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return false;
	}

	// X軸の値の範囲設定
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.diph.dwObj = DIJOFS_X;
	diprg.lMin = -1000;
	diprg.lMax = 1000;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// Y軸の値の範囲設定
	diprg.diph.dwObj = DIJOFS_Y;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	return true;
}

// 戻り値　デバイス列挙を継続するか？
// true : Yes(Continue)  false : No(Stop)
// DEVICEINSTANCE : 列挙されたデバイス(デバイス識別子、製品の識別子、デバイスのタイプ、登録名、製品名)
//					最低限必要なのはデバイス識別子のみ => CreateDevice
// LPVOID : EnumDevicesで渡した値
BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	DeviceEnumParameter* parameter = (DeviceEnumParameter*)pvRef;
	LPDIRECTINPUTDEVICE8 device = nullptr;

	if (parameter->FindCount >= 1)
	{
		return DIENUM_STOP;
	}

	HRESULT hr = g_InputInterface->CreateDevice(
		lpddi->guidInstance,
		parameter->GamePadDevice,
		NULL);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	device = *parameter->GamePadDevice;
	hr = device->SetDataFormat(&c_dfDIJoystick);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	if (SetUpGamePadProperty(device) == false)
	{
		return DIENUM_STOP;
	}

	if (SetUpCooperativeLevel(device) == false)
	{
		return DIENUM_STOP;
	}

	//if (FAILED(device->Poll()))
	//{
	//	return DIENUM_STOP;
	//}

	parameter->FindCount++;

	return DIENUM_CONTINUE;
}


bool InitInput()
{
	if (CreateInputInterface() == false)
	{
		return false;
	}

	if (CreateMouseDevice() == false)
	{
		EndInput();
		return false;
	}

	if (CreateKeyboardDevice() == false) {
		EndInput();
		return false;
	}

	if (CreateGamePadDevice() == false)
	{
		EndInput();
		return false;
	}

	for (int i = 0; i < ButtonKind::ButtonKindMax; i++)
	{
		g_ButtonStates[i] = ButtonState::ButtonStateNone;
	}

	ZeroMemory(&g_CurrentMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&g_PrevMouseState, sizeof(DIMOUSESTATE));

	return true;
}

void EndInput()
{
	if (g_MouseDevice != nullptr)
	{
		g_MouseDevice->Release();
		g_MouseDevice = nullptr;
	}

	if (g_GamePadDevice != nullptr)
	{
		g_GamePadDevice->Release();
		g_GamePadDevice = nullptr;
	}

	if (g_InputInterface != nullptr)
	{
		g_InputInterface->Release();
		g_InputInterface = nullptr;
	}

	if (g_pKeyDevice != nullptr)
	{
		g_pKeyDevice->Release();
		g_pKeyDevice = nullptr;
	}
}


void UpdateInput()
{
	UpdateMouse();
	UpDateKey();
	UpdateGamePad();

	g_PrevMouseState = g_CurrentMouseState;
	// マウスの状態を取得します
	HRESULT	hr = g_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);
	if (FAILED(hr))
	{
		g_MouseDevice->Acquire();
		hr = g_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);
	}
}


bool OnMouseDown(MouseButton button_type)
{
	if (!(g_PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE) &&
		g_CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE)
	{
		return true;
	}

	return false;
}

bool OnMousePush(MouseButton button_type)
{
	if (g_PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE &&
		g_CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE)
	{
		return true;
	}

	return false;
}

bool OnMouseUp(MouseButton button_type)
{
	if (g_PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE &&
		!(g_CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE))
	{
		return true;
	}

	return false;
}

void UpdateMouse()
{
	Vec2 prev = g_MousePos;
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(FindWindowA(WINDOW_CLASS_NAME, nullptr), &p);

	g_MousePos.X = (float)p.x;
	g_MousePos.Y = (float)p.y;

	g_MouseMoveVec.X = g_MousePos.X - prev.X;
	g_MouseMoveVec.Y = g_MousePos.Y - prev.Y;
}

Vec2 GetMousePos()
{
	return g_MousePos;
}

bool CreateInputInterface()
{
	HRESULT ret = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)& g_InputInterface, nullptr);
	if (FAILED(ret))
	{
		return false;	// 作成に失敗
	}

	return true;
}

bool CreateGamePadDevice()
{
	DeviceEnumParameter parameter;

	parameter.FindCount = 0;
	parameter.GamePadDevice = &g_GamePadDevice;

	// 指定したデバイスを列挙する（今回であればゲームパッド）
	if (FAILED(g_InputInterface->EnumDevices(
		DI8DEVTYPE_GAMEPAD,
		DeviceFindCallBack,		// 第2引数：コールバック関数
		&parameter,				// 第3引数：コールバック関数に渡すことができるデータ
		DIEDFL_ATTACHEDONLY		// 第4引数：現状でささっているデバイスのみを使用する設定
	)))
	{
		return false;
	}

	/*if (parameter.FindCount == 0)
	{
		return false;
	}*/

	int count = 0;
	while (StartGamePadControl() == false)
	{
		Sleep(1000);
		count++;
		if (count >= 5)
		{
			break;
		}
	}

	return true;
}

bool CreateMouseDevice()
{
	// マウス用にデバイスオブジェクトを作成
	if (FAILED(g_InputInterface->CreateDevice(GUID_SysKeyboard, &g_pKeyDevice, nullptr)))
	{
		// デバイスの作成に失敗
		return false;
	}

	// データフォーマットを設定
	if (FAILED(g_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		// データフォーマットに失敗
		return false;
	}

	// モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(g_pKeyDevice->SetCooperativeLevel(
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		// モードの設定に失敗
		return false;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	if (FAILED(g_pKeyDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// デバイスの設定に失敗
		return false;
	}

	// 入力制御開始
	g_pKeyDevice->Acquire();

	return true;
}


bool CreateKeyboardDevice()
{
	// マウス用にデバイスオブジェクトを作成
	if (FAILED(g_InputInterface->CreateDevice(GUID_SysMouse, &g_MouseDevice, nullptr)))
	{
		// デバイスの作成に失敗
		return false;
	}

	// データフォーマットを設定
	if (FAILED(g_MouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		// データフォーマットに失敗
		return false;
	}

	// モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(g_MouseDevice->SetCooperativeLevel(
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		// モードの設定に失敗
		return false;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	if (FAILED(g_MouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// デバイスの設定に失敗
		return false;
	}

	// 入力制御開始
	g_MouseDevice->Acquire();

	return true;
}
void UpDateKey()
{
	// キー情報取格納用
	BYTE KeyState[256];
	HRESULT hr;

	// キーボードデバイスのゲッター
	hr = g_pKeyDevice->GetDeviceState(256, KeyState);
	if (SUCCEEDED(hr))
	{
		// 1フレーム前のキー情報の確保
		DWORD old = g_InputState.now;

		// キー情報クリア
		g_InputState.now = CLEAR_KEY;

		// 上キー
		if (KeyState[DIK_UP] & 0x80)
		{
			g_InputState.now |= UP_KEY;
		}

		// 下キー
		if (KeyState[DIK_DOWN] & 0x80)
		{
			g_InputState.now |= DOWN_KEY;
		}

		// 左キー
		if (KeyState[DIK_LEFT] & 0x80)
		{
			g_InputState.now |= LEFT_KEY;
		}

		// 右キー
		if (KeyState[DIK_RIGHT] & 0x80)
		{
			g_InputState.now |= RIGHT_KEY;
		}

		// リターンキー
		if (KeyState[DIK_RETURN] & 0x80)
		{
			g_InputState.now |= RETURN_KEY;
		}
		if (KeyState[DIK_A] & 0x80)
		{
			g_InputState.now |= A_KEY;
		}
		if (KeyState[DIK_SPACE] & 0x80)
		{
			g_InputState.now |= SPACE_KEY;
		}
		if (KeyState[DIK_1] & 0x80)
		{
			g_InputState.now |= ONE_KEY;
		}
		if (KeyState[DIK_2] & 0x80)
		{
			g_InputState.now |= TWO_KEY;
		}
		if (KeyState[DIK_3] & 0x80)
		{
			g_InputState.now |= THREE_KEY;
		}
		if (KeyState[DIK_LSHIFT] & 0x80)
		{
			g_InputState.now |= SHIFT_KEY;
		}
		if (KeyState[DIK_E] & 0x80) 
		{
			g_InputState.now |= E_KEY;
		}
		

		g_InputState.trg = (g_InputState.now & (~old));	// トリガー情報取得
		g_InputState.ntrg = (~g_InputState.now) & old;	// 逆トリガー情報取得

	}
	else if (hr == DIERR_INPUTLOST) {
		g_pKeyDevice->Acquire();
	}
}

void UpdateGamePad()
{

	if (g_GamePadDevice == nullptr)
	{
		return;
	}

	DIJOYSTATE pad_data;
	HRESULT hr = g_GamePadDevice->GetDeviceState(sizeof(DIJOYSTATE), &pad_data);
	if (FAILED(hr))
	{
		if (FAILED(g_GamePadDevice->Acquire()))
		{
			for (int i = 0; i < ButtonKind::ButtonKindMax; i++)
			{
				g_ButtonStates[i] = ButtonState::ButtonStateNone;
			}
		}
	}

	bool is_push[ButtonKind::ButtonKindMax] = { false };

	if (pad_data.lX < -200)
	{
		is_push[ButtonKind::LeftButton] = true;
	}
	else if (pad_data.lX > 200)
	{
		is_push[ButtonKind::RightButton] = true;
	}

	if (pad_data.lY < 200)
	{
		is_push[ButtonKind::UpButton] = true;
	}
	else if (pad_data.lY > 200)
	{
		is_push[ButtonKind::DownButton] = true;
	}

	// 十字キー
	if (pad_data.rgdwPOV[0] != 0xFFFFFFFF)
	{
		float rad = D3DXToRadian((pad_data.rgdwPOV[0] / 100.0f));
		// 本来はxがcos、yがsinだけど、rgdwPOVは0が上から始まるので、
		// cosとsinを逆にした方が都合がいい
		float x = sinf(rad);
		float y = cosf(rad);

		if (x < -0.01f)
		{
			is_push[ButtonKind::LeftButton] = true;
		}
		else if (x > 0.01f)
		{
			is_push[ButtonKind::RightButton] = true;
		}

		if (y > 0.01f)
		{
			is_push[ButtonKind::UpButton] = true;
		}
		else if (y < -0.01f)
		{
			is_push[ButtonKind::DownButton] = true;
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		if (pad_data.rgbButtons[i] == 0x80)
		{
			is_push[i] = true;
		}
		else {
			is_push[i] = false;
		}
	}
	

	for (int i = 0; i < ButtonKind::ButtonKindMax; i++)
	{
		if (is_push[i] == true)
		{
			if (g_ButtonStates[i] == ButtonState::ButtonStateNone)
			{
				g_ButtonStates[i] = ButtonState::ButtonStateDown;
			}
			else
			{
				g_ButtonStates[i] = ButtonState::ButtonStatePush;
			}
		}
		else
		{
			if (g_ButtonStates[i] == ButtonState::ButtonStatePush)
			{
				g_ButtonStates[i] = ButtonState::ButtonStateUp;
			}
			else
			{
				g_ButtonStates[i] = ButtonState::ButtonStateNone;
			}
		}
	}
}

bool GetKey(DWORD key_code)
{
	return g_InputState.now& key_code;
}

bool GetKeyDown(DWORD key_code)
{
	return g_InputState.trg& key_code;
}

bool GetKeyUp(DWORD key_code)
{
	return g_InputState.ntrg& key_code;
}

bool IsButtonPush(ButtonKind button)
{
	if (g_ButtonStates[button] == ButtonState::ButtonStatePush)
	{
		return true;
	}

	return false;
}

bool IsButtonUp(ButtonKind button)
{
	if (g_ButtonStates[button] == ButtonState::ButtonStateUp)
	{
		return true;
	}

	return false;
}

bool IsButtonDown(ButtonKind button)
{
	if (g_ButtonStates[button] == ButtonState::ButtonStateDown)
	{
		return true;
	}

	return false;
}