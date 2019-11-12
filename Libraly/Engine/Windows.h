/**
* @file Window.h
* @brief �E�B���h�E�Ɋւ���O�����J�֐��A�萔�̐錾
*/
#ifndef WINDOW_H_
#define WINDOW_H_

#include <Windows.h>

#define WINDOW_CLASS_NAME "Window"	//!< �E�B���h�E�N���X��

/**
* @brief �E�B���h�E�����֐�@n
* �����Ŏw�肳�ꂽ���e�ŃE�B���h�E���쐬����
* @return ��������(������true)
* @param[in] width ����
* @param[in] height �c��
* @param[in] title �^�C�g���o�[�ɕ\������镶����
*/
bool MakeWindow(int width, int height, const char* title);

HWND GetWindowHandle();

#endif


