#include <d3d9.h>
#include <d3dx9.h>
#include "../Engine/Graphics.h"
#include "../Engine/Windows.h"
#include "../Utility/Size.h"
#include "../Engine/Vec.h"


// �ÓI���C�u����
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

struct CustomVertex
{
	float X;			// X���W
	float Y;			// Y���W
	float Z;			// Z���W	
	float Rhw;			// ���Z��

	float TextureX;		// �e�N�X�`�����WX
	float TexrureY;		// �e�N�X�`�����WY
};

/*
	static���O���[�o���ϐ��Ɏw�肷���
	�ʂ�cpp����̃A�N�Z�X���ł��Ȃ��Ȃ�

		�����b�g
			���ʂȃA�N�Z�X�����点��

	static�Ƃ��� => �����Ȃ𖾎����Ă�
*/

// �O���[�o���ϐ�
static LPDIRECT3D9 g_D3DInterface;						// DirectGraphics�C���^�[�t�F�[�X
static LPDIRECT3DDEVICE9 g_D3DDevice;					// DirectGraphics�f�o�C�X
static LPD3DXFONT g_FontList[FontSize::FontSizeMax];	// �t�H���g�f�o�C�X���X�g

// �C���^�[�t�F�[�X�̍쐬
bool CreateGraphicsInterface();

// �O���t�B�b�N�f�o�C�X�̍쐬
bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param);

// ViewPort�̐ݒ�
bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param);

// �t�H���g�f�o�C�X�̐���
bool CreateFontDevice();

bool InitGraphics()
{
	D3DPRESENT_PARAMETERS present_param;
	ZeroMemory(&present_param, sizeof(D3DPRESENT_PARAMETERS));

	if (CreateGraphicsInterface() == false)
	{
		return false;
	}

	if (CreateGraphicsDevice(&present_param) == false)
	{
		return false;
	}

	if (SetUpViewPort(&present_param) == false)
	{
		return false;
	}

	if (CreateFontDevice() == false)
	{
		return false;
	}

	return true;
}

void EndGraphics()
{
	for (int i = 0; i < FontSize::FontSizeMax; i++)
	{
		g_FontList[i]->Release();
	}
	g_D3DDevice->Release();
	g_D3DInterface->Release();
}

bool DrawStart()
{
	g_D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

	g_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	if (D3D_OK == g_D3DDevice->BeginScene())
	{
		return true;
	}

	return false;
}

void DrawEnd()
{
	g_D3DDevice->EndScene();
	g_D3DDevice->Present(NULL, NULL, NULL, NULL);
}


void DrawTexture(float x, float y, Texture* texture_data)
{
	CustomVertex v[4] =
	{
		{ x, y, 0.0f, 1.0f, 0.0f, 0.0f },
		{ x + texture_data->Width, y, 0.0f, 1.0f, 1.0f, 0.0f },
		{ x + texture_data->Width, y + texture_data->Height, 0.0f, 1.0f, 1.0f, 1.0f },
		{ x, y + texture_data->Height, 0.0f, 1.0f, 0.0f, 1.0f },
	};

	// ���_�\���̎w��
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TextureData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}




//�����摜�؂蔲���p
void DrawIntegratedTexture(float x, float y, Texture * texture_data, float tu, float tv, float spriteX, float spriteY, int spriteNumX, int spriteNumY)
{

	int tmpX = spriteNumX - 1;
	int tmpY = spriteNumY - 1;

	CustomVertex v[4] =
	{
		{ x, y, 0.0f, 1.0f, tu * tmpX, tv * tmpY },
		{ x + spriteX, y, 0.0f, 1.0f, tu * spriteNumX, tv * tmpY },
		{ x + spriteX, y + spriteY, 0.0f, 1.0f, tu * spriteNumX, tv * spriteNumY },
		{ x, y + spriteY, 0.0f, 1.0f, tu * tmpX, tv * spriteNumY},
	};

	// ���_�\���̎w��
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TextureData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

//�����摜�؂蔲���p
void DrawObjIntegratedTexture(float x, float y, Texture * texture_data, float tu, float tv, float spriteX, float spriteY, int spriteNumX, int spriteNumY, float z)
{

	int tmpX = spriteNumX - 1;
	int tmpY = spriteNumY - 1;

	CustomVertex v[4] =
	{
		{ x, y, z, 1.0f, tu * tmpX, tv * tmpY },
		{ x + spriteX, y, z, 1.0f, tu * spriteNumX, tv * tmpY },
		{ x + spriteX, y + spriteY, z, 1.0f, tu * spriteNumX, tv * spriteNumY },
		{ x, y + spriteY, z, 1.0f, tu * tmpX, tv * spriteNumY},
	};

	// ���_�\���̎w��
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TextureData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

//�e�X�g��
void DrawAnimeTexture(float x, float y, Texture * texture_data, float tu, float tv, int divisionX, int divisionY, int Animetion)
{

	CustomVertex v[4] =
	{
		{ x, y, 0.0f, 1.0f, 0.0f, 0.0f },
		{ x + (texture_data->Width / divisionX), y, 0.0f, 1.0f, tu, 0.0f },
		{ x + (texture_data->Width / divisionX), y + (texture_data->Height / divisionY), 0.0f, 1.0f, tu, tv},
		{ x, y + (texture_data->Height / divisionY), 0.0f, 1.0f, 0.0f, tv},
	};

	switch (Animetion) {
	case BOMB_SPRITE_NUM:
		v[0].TextureX += tu * 4;
		v[1].TextureX += tu * 4;
		v[2].TextureX += tu * 4;
		v[3].TextureX += tu * 4;
		break;
	case (BOMB_SPRITE_NUM - 1):
		v[0].TextureX += tu * 3;
		v[1].TextureX += tu * 3;
		v[2].TextureX += tu * 3;
		v[3].TextureX += tu * 3;
		break;
	case (BOMB_SPRITE_NUM - 2):
		v[0].TextureX += tu * 2;
		v[1].TextureX += tu * 2;
		v[2].TextureX += tu * 2;
		v[3].TextureX += tu * 2;
		break;
	case (BOMB_SPRITE_NUM - 3):
		v[0].TextureX += tu;
		v[1].TextureX += tu;
		v[2].TextureX += tu;
		v[3].TextureX += tu;
		break;
	case (BOMB_SPRITE_NUM - 4):
		break;
	default:
		break;
	}

	// ���_�\���̎w��
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TextureData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

//�e�X�g��
void DrawAnimeTexture2(float x, float y, Texture * texture_data, float tu, float tv, int divisionX, int divisionY, int Animetion)
{

	CustomVertex v[4] =
	{
		{ x, y, 0.0f, 1.0f, 0.0f, 0.0f },
		{ x + (texture_data->Width / divisionX), y, 0.0f, 1.0f, tu, 0.0f },
		{ x + (texture_data->Width / divisionX), y + (texture_data->Height / divisionY), 0.0f, 1.0f, tu, tv},
		{ x, y + (texture_data->Height / divisionY), 0.0f, 1.0f, 0.0f, tv},
	};


	for (int i = 0; i < 4; i++) {
		v[i].TextureX += tu * Animetion;
	}


	// ���_�\���̎w��
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TextureData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

void DrawUVScrollTexture(float x, float y, Texture * texture_data, float tu, float tv)
{
	CustomVertex v[4] =
	{
		{ x, y, 0.0f, 1.0f, tu, tv },
		{ x + texture_data->Width, y, 0.0f, 1.0f, tu + 1.0f, tv },
		{ x + texture_data->Width, y + texture_data->Height, 0.0f, 1.0f, tu + 1.0f, tv + 1.0f },
		{ x, y + texture_data->Height, 0.0f, 1.0f, tu, tv + 1.0f },
	};

	// ���_�\���̎w��
	g_D3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	g_D3DDevice->SetTexture(0, texture_data->TextureData);

	g_D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CustomVertex));
}

//�I�I�I�e�X�g���I�I�I
float center_x, center_y;



void DrawFont(float pos_x, float pos_y, const char* text, FontSize font_type, FontColor color)
{
	RECT rect =
	{
		(long)pos_x,
		(long)pos_y,
		(long)pos_x + 400,
		(long)pos_y + 200,
	};

	int r, g, b;
	r = g = b = 255;

	if (color == FontColor::Black)
	{
		r = g = b = 0;
	}
	else if (color == FontColor::Red)
	{
		r = 255;
		g = b = 0;
	}

	g_FontList[font_type]->DrawTextA(
		NULL,
		text,
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_XRGB(r, g, b)
	);
}

bool CreateTexture(const char* file_name, Texture * texture_data)
{
	Size size;
	D3DXIMAGE_INFO info;

	// 2�̗ݏ悶��Ȃ��P�[�X��z�肵�Č��̃T�C�Y���擾����D3DXCreateTextureFromFileEx�Ŏg��
	D3DXGetImageInfoFromFileA(file_name, &info);

	if (FAILED(D3DXCreateTextureFromFileExA(g_D3DDevice,
		file_name,
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		nullptr,
		nullptr,
		&texture_data->TextureData)))
	{
		return false;
	}
	else
	{
		// �e�N�X�`���T�C�Y�̎擾
		D3DSURFACE_DESC desc;

		if (FAILED(texture_data->TextureData->GetLevelDesc(0, &desc)))
		{
			texture_data->TextureData->Release();
			return false;
		}
		texture_data->Width = desc.Width;
		texture_data->Height = desc.Height;
	}

	return true;
}



bool CreateGraphicsInterface()
{
	// �C���^�[�t�F�[�X�쐬
	g_D3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_D3DInterface == NULL)
	{
		// �쐬���s
		return false;
	}

	// �쐬����
	return true;
}

bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS * present_param)
{
	//���̉𑜓x
	present_param->BackBufferWidth = 1920;
	//�c�̉𑜓x
	present_param->BackBufferHeight = 1080;
	//�f�B�X�v���C���[�h
	present_param->BackBufferFormat = D3DFMT_A8R8G8B8;
	//�}���`�T���v���̐�
	present_param->MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	//�}���`�T���v���̕i�����x��
	present_param->MultiSampleQuality = 0;
	//�[�x�X�e���V���o�b�t�@�����邩�ǂ���
	present_param->EnableAutoDepthStencil = TRUE;
	//�X�e���V���o�b�t�@�̃t�H�[�}�b�g
	present_param->AutoDepthStencilFormat = D3DFMT_D24S8;
	//�o�b�N�o�b�t�@����t�����g�o�b�t�@�֓]�����̃I�v�V����
	present_param->Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	//�t���X�N���[���̃��t���b�V�����[�g
	present_param->FullScreen_RefreshRateInHz = 0;
	//�X���b�v�G�t�F�N�g�̏��������^�C�~���O
	present_param->PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	// �o�b�N�o�b�t�@�̐� => 1
	present_param->BackBufferCount = 1;

	// �E�B���h�E���[�h�ݒ� => �萔�Ő؂�ւ�
	present_param->Windowed = false;

	// �X���b�v�G�t�F�N�g => �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�ւ̐؂�ւ����@
	present_param->SwapEffect = D3DSWAPEFFECT_DISCARD;

	// DirectDevice�̍쐬
	if (FAILED(g_D3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		FindWindowA(WINDOW_CLASS_NAME, nullptr),
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		present_param,
		&g_D3DDevice)))
	{
		return false;
	}

	return true;
}

bool SetUpViewPort(D3DPRESENT_PARAMETERS * present_param)
{
	// �r���[�|�[�g�p�����[�^
	D3DVIEWPORT9 view_port;

	// �r���[�|�[�g�̍�����W
	view_port.X = 0;
	view_port.Y = 0;
	// �r���[�|�[�g�̕�
	view_port.Width = present_param->BackBufferWidth;
	// �r���[�|�[�g�̍���
	view_port.Height = present_param->BackBufferHeight;
	// �r���[�|�[�g�[�x�ݒ�
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// �r���[�|�[�g�ݒ�
	if (FAILED(g_D3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

bool CreateFontDevice()
{
	int size_list[] =
	{
		SMALL_FONT_SIZE,
		REGULAR_FONT_SIZE,
		LARGE_FONT_SIZE
	};

	for (int i = 0; i < FontSize::FontSizeMax; i++)
	{
		if (FAILED(D3DXCreateFont(g_D3DDevice,
			size_list[i],
			size_list[i] / 2,
			FW_REGULAR,
			NULL,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_SCRIPT,
			TEXT("�l�r�@�o�S�V�b�N"),
			&g_FontList[i])))
		{
			return false;
		}
	}

	return true;
}
