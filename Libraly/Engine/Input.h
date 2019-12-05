
/**
* @file Input.h
* @brief ���͂Ɋւ���֐��A�萔�̐錾
*/
#ifndef INPUT_H_
#define INPUT_H_

#include <Windows.h>
#include "../Engine/Vec.h"

// �L�[���GetKey�V���[�Y�̊֐��Ŏg�p����
#define CLEAR_KEY	0x0000		// �L�[�N���A�p
#define UP_KEY		0x0001		// ��L�[
#define DOWN_KEY	0x0002		// ���L�[
#define LEFT_KEY	0x0004		// ���L�[
#define RIGHT_KEY	0x0008		// �E�L�[
#define RETURN_KEY	0x0010		// ���^�[���L�[
#define W_KEY		0x0020		// W�L�[
#define A_KEY		0x0040		// A�L�[
#define S_KEY		0x0080		// S�L�[
#define D_KEY		0x0100		// D�L�[
#define SPACE_KEY   0x0200      // SPACE�L�[
#define ONE_KEY     0x0400      // 1�L�[
#define TWO_KEY     0x0800      // 2�L�[
#define THREE_KEY   0x1600		// 3�L�[
#define SHIFT_KEY   0x3200		// Shift�L�[

/** @brief �}�E�X�{�^���̎�� */
enum MouseButton
{
	Left,		//!< ��
	Right,		//!< �E
	Center,		//!< �^��
};

/**
* @brief Input�@�\�������֐�@n
* �f�o�C�X�̓��͎擾�ɕK�v�ȏ��������s��
* ��InitEngine�Ŏ��s�����̂ŊJ���������s����K�v�͂Ȃ�
* @return ����������(������true)
*/
bool InitInput();

/**
* @brief Input�@�\�I���֐�@n
* Input�@�\���I��������@n
* ��EndEngine�Ŏ��s�����̂ŊJ���������s����K�v�͂Ȃ�
*/
void EndInput();

/**
* @brief ���͏��̍X�V@n
* �f�o�C�X�̓��͏��̍X�V���s��@n
* ���t���[���ɂP�x�K�����s����K�v������
*/
void UpdateInput();

/**
* @brief �N���b�N�����u�Ԕ���֐�@n
* �w�肵���}�E�X�̃{�^�����N���b�N���ꂽ�u�Ԃ��ǂ����𔻒肷��
* @return ���茋��(�����ꂽ�u�ԂȂ�true)
* @param[in] button_type ���肵�����{�^���̎��
*/
bool OnMouseDown(MouseButton button_type);

/**
* @brief �N���b�N������֐�@n
* �w�肵���}�E�X�̃{�^�����N���b�N�����ǂ����𔻒肷��
* @return ���茋��(�N���b�N���u�ԂȂ�true)
* @param[in] button_type ���肵�����{�^���̎��
*/
bool OnMousePush(MouseButton button_type);

/**
* @brief �N���b�N�I������֐�@n
* �w�肵���}�E�X�̃{�^�����N���b�N���I�������u�Ԃ��ǂ����𔻒肷��
* @return ���茋��(�N���b�N����߂��u�ԂȂ�true)
* @param[in] button_type ���肵�����{�^���̎��
*/
bool OnMouseUp(MouseButton button_type);

/** @brief �}�E�X�̍��W�擾�֐� */
Vec2 GetMousePos();

bool CreateKeyboardDevice();
void UpDateKey();
bool GetKey(DWORD key_code);
bool GetKeyDown(DWORD key_code);
bool GetKeyUp(DWORD key_code);
#endif


