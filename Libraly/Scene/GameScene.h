/**
* @file GameScene.h
* @brief �Q�[���{�҃V�[���̊֐��̐錾
*/
#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "../Scene/Scene.h"

/**
* @brief �Q�[���{�҃V�[���̍X�V�֐�@n
* �Q�[���{�҃V�[���̎d�l�����s�����
* @return �J�ڐ�V�[��ID(��{��SceneId::GameScene���Ԃ�)
*/
SceneId UpdateGameScene();

/**a
* @brief �Q�[���{�҃V�[���̕`��֐�@n
* �Q�[���{�҃V�[���̃I�u�W�F�N�g��`�悷�邽�߂̊֐�
*/
void DrawGameScene();

void ChangeResearchFlag(bool OnOff);

void ChangeEventFlag(bool OnOff);
bool CheckEventFlag();

#endif


