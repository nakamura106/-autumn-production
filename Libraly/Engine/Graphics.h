/**
* @file Graphics.h
* @brief �`��Ɋւ���֐��A�萔�̐錾
*/
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <Windows.h>
#include <d3d9.h>
#include"../Object/Definition.h"

/** @brief �t�H���g�J���[ */
enum FontColor
{
	Black,			//!< ��
	White,			//!< ��
	Red,			//!< ��
};

// @brief �t�H���g�T�C�Y */
enum FontSize
{
	Small,			//!< ��
	Regular,		//!< ��
	Large,			//!< ��
	FontSizeMax,	//!< �T�C�Y�ő吔
};

#define SMALL_FONT_SIZE (16)	//!< �t�H���g�T�C�Y(��)
#define REGULAR_FONT_SIZE (24)	//!< �t�H���g�T�C�Y(��)
#define LARGE_FONT_SIZE (32)	//!< �t�H���g�T�C�Y(��)

/** @brief �e�N�X�`���f�[�^��T�C�Y��ێ�����\���� */
struct Texture
{
	LPDIRECT3DTEXTURE9 TextureData;	//!< �e�N�X�`���f�[�^
	int Width;						//!< ����
	int Height;						//!< �c��
};


/**
* @brief Graphics�@�\�������֐�@n
* �`��֘A���g�p�\�ɂ��邽�߂̏��������s��@n
* ��Engine.cpp��InitEngine�Ŏ��s���Ă���̂�@n
* �@�g�p�҂͎��������Ŏg���K�v�͂Ȃ�
* @return ���������� (true������)
*/
bool InitGraphics();

/**
* @brief Graphics�@�\�I���֐�@n
* �`��֘A�̏����̌�n�����s������@n
* ��Engine.cpp��EndEngine�Ŏ��s���Ă���̂�@n
* �@�g�p�҂͎��������Ŏg���K�v�͂Ȃ�
*/
void EndGraphics();

/**
* @brief �`��J�n�֐�@n
* �`��J�n��錾���A�o�b�N�o�b�t�@�̃N���A���s��
* @return �`��J�n�̐��� (������true)
*/
bool DrawStart();

/**
* @brief �`��I���֐�@n
* �`��̏I����錾���A�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���@n
* �����̊֐��͕K��DrawStart�̌�Ɏ��s�����悤�ɂ��Ă��������B
*/
void DrawEnd();

/**
* @brief �e�N�X�`���`��֐�@n
* �w�肳�ꂽ�ʒu�Ƀe�N�X�`����`�悷��@n
* ��texture_data��File.h��GetTextureData���g�p���Ă��������B
* @param[in] x X���`����W
* @param[in] y Y���`����W
* @param[in] texture_data �`��Ŏg�p����e�N�X�`���̃f�[�^
*/
void DrawTexture(float x, float y, Texture* texture_data);

/**
* @brief �e�N�X�`����UV�X�N���[���`��֐�@n
* �w�肳�ꂽ���Ńe�N�X�`����UV�X�N���[�����ĕ`�悷��@n
* ��texture_data��File.h��GetTextureData���g�p���Ă��������B
* @param[in] x X���`����W
* @param[in] y Y���`����W
* @param[in] texture_data �`��Ŏg�p����e�N�X�`���̃f�[�^
* @param[in] tu �e�N�X�`��U���W
* @param[in] tv �e�N�X�`��V���W
*/

void DrawUVTexture(float x, float y, float sprite_width, float sprite_height, Texture* texture_data, float tu, float tv, bool is_turn = false);

void DrawUVScrollTexture(float x, float y, Texture* texture_data, float tu, float tv);


// �X���C�_�[�Ŏg�p����
void DrawUVMappingTexture(float x, float y, Texture* texture_data, float texture_x, float texture_y, float rect_width, float rect_height);

//���E���]�p
void DrawInversion(float x, float y, float sprite_width, float sprite_height, Texture* texture_data, float tu, float tv, int direction);


/**
* @brief �t�H���g�`��֐�@n
* �w�肳�ꂽ�ʒu�Ƀt�H���g��`�悷��@n
* @param[in] x X���`����W
* @param[in] y Y���`����W
* @param[in] text �`�悷��e�L�X�g
* @param[in] size �t�H���g�T�C�Y�̎��
* @param[in] color �t�H���g�̐F
*/
void DrawFont(float pos_x, float pos_y, const char* text, FontSize size, FontColor color);

/**
* @brief �e�N�X�`���쐬@n
* �w�肳�ꂽ��񂩂�ǂݍ��݁A�e�N�X�`�����쐬����@n
* ���J������File.h��LoadTexture���g�p���Ă��������B
* @return �쐬����(������true)
* @param[in] file_name �ǂݍ��ރe�N�X�`���̖��O(�p�X����)
* @param[out] texture_data �ǂݍ��܂ꂽ�e�N�X�`���𔽉f����f�[�^
*/
bool CreateTexture(const char* file_name, Texture* texture_data);

#define BOMB_SPRITE_NUM (5)

//�����摜����e�N�X�`���𔲂��o���ĕ`��ł��܂�
//(x, y, texture_data)�͏]���ʂ�̎g�p���@��OK
//�������A�ϓ��ɕ�������Ă��铝���摜�̂ݎg�p�\
//texNumX => X���������w��(1~)
//texNumY => Y���̖������w��(1~)
//divisionX => �����摜�̕��������w�� X��
//divisionY => �����摜�̕��������w�� Y��
void DrawAdvTexture(float x, float y, Texture* texture_data, float texNumX, float texNumY, int divisionX, int divisionY);

//�摜���A�j���[�V�������邱�Ƃ��ł��܂�
//�v�Z���������G�Ȃ̂�TitleScene�̃{�������Q�l�ɂ��Ă�������
void DrawAnimeTexture(float x, float y, Texture* texture_data, float tu, float tv, int divisionX, int divisionY, int Animetion);

void PlayerDrawTexture(float x, float y, float rotate, Texture* texture_data);

void EnemyDrawTexture(float x, float y, float rotate, Texture* texture_data, int i);

//�����摜����؂蔲���p�̊֐�
//�S�Ă̐؂蔲�����摜�̑傫�������ł���K�v������
//tu,tv => �摜�̊���
//tv,tv = (�؂蔲�����摜�T�C�Y / �����摜�̃T�C�Y)
//spriteX,spriteY => �؂蔲�����摜�T�C�Y
//spriteNumX,spriteNumY => �؂蔲�������摜�̍��W
void DrawIntegratedTexture(float x, float y, Texture* texture_data, float tu, float tv, float spriteX, float spriteY, int spriteNumX, int spriteNumY);

void DrawObjIntegratedTexture(float x, float y, Texture* texture_data, float tu, float tv, float spriteX, float spriteY, int spriteNumX, int spriteNumY, float z);

void DrawEffect(EffectInfo effect);

#endif

