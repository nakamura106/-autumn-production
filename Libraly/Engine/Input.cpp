#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Windows.h>
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

static LPDIRECTINPUT8 g_InputInterface;		//!< DIRECTINPUT8�̃|�C���^
static LPDIRECTINPUTDEVICE8 g_MouseDevice;		//!< DIRECTINPUTDEVICE8�̃|�C���^
static DIMOUSESTATE g_PrevMouseState;			//!< �}�E�X�̂P�t���[���O�̓��͏��
static DIMOUSESTATE g_CurrentMouseState;		//!< �}�E�X�̌��݂̓��͏��
static Vec2 g_MousePos;
static Vec2 g_MouseMoveVec;

// ���̓C���^�[�t�F�[�X�̍쐬
bool CreateInputInterface();

// �}�E�X�f�o�C�X�̍쐬
bool CreateMouseDevice();

// �}�E�X�̍X�V
void UpdateMouse();

#define MOUSE_ON_VALUE (0x80)		// �I����Ԃ̒l

static LPDIRECTINPUTDEVICE8 g_pKeyDevice;

// �L�[���
static INPUTSTATE g_InputState;


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

	g_PrevMouseState = g_CurrentMouseState;
	// �}�E�X�̏�Ԃ��擾���܂�
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
		return false;	// �쐬�Ɏ��s
	}

	return true;
}

bool CreateMouseDevice()
{
	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	if (FAILED(g_InputInterface->CreateDevice(GUID_SysKeyboard, &g_pKeyDevice, nullptr)))
	{
		// �f�o�C�X�̍쐬�Ɏ��s
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		// �f�[�^�t�H�[�}�b�g�Ɏ��s
		return false;
	}

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(g_pKeyDevice->SetCooperativeLevel(
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		// ���[�h�̐ݒ�Ɏ��s
		return false;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED(g_pKeyDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return false;
	}

	// ���͐���J�n
	g_pKeyDevice->Acquire();

	return true;
}


bool CreateKeyboardDevice()
{
	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	if (FAILED(g_InputInterface->CreateDevice(GUID_SysMouse, &g_MouseDevice, nullptr)))
	{
		// �f�o�C�X�̍쐬�Ɏ��s
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_MouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		// �f�[�^�t�H�[�}�b�g�Ɏ��s
		return false;
	}

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(g_MouseDevice->SetCooperativeLevel(
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		// ���[�h�̐ݒ�Ɏ��s
		return false;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED(g_MouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return false;
	}

	// ���͐���J�n
	g_MouseDevice->Acquire();

	return true;
}
void UpDateKey()
{
	// �L�[����i�[�p
	BYTE KeyState[256];
	HRESULT hr;

	// �L�[�{�[�h�f�o�C�X�̃Q�b�^�[
	hr = g_pKeyDevice->GetDeviceState(256, KeyState);
	if (SUCCEEDED(hr))
	{
		// 1�t���[���O�̃L�[���̊m��
		DWORD old = g_InputState.now;

		// �L�[���N���A
		g_InputState.now = CLEAR_KEY;

		// ��L�[
		if (KeyState[DIK_UP] & 0x80)
		{
			g_InputState.now |= UP_KEY;
		}

		// ���L�[
		if (KeyState[DIK_DOWN] & 0x80)
		{
			g_InputState.now |= DOWN_KEY;
		}

		// ���L�[
		if (KeyState[DIK_LEFT] & 0x80)
		{
			g_InputState.now |= LEFT_KEY;
		}

		// �E�L�[
		if (KeyState[DIK_RIGHT] & 0x80)
		{
			g_InputState.now |= RIGHT_KEY;
		}

		// ���^�[���L�[
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
		

		g_InputState.trg = (g_InputState.now & (~old));	// �g���K�[���擾
		g_InputState.ntrg = (~g_InputState.now) & old;	// �t�g���K�[���擾

	}
	else if (hr == DIERR_INPUTLOST) {
		g_pKeyDevice->Acquire();
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
