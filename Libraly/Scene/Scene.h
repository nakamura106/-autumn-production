/**
* @file Scene.h
* @brief �V�[���S�̂����s�A�`�悷��֐��̐錾
*/
#ifndef SCENE_H_
#define SCENE_H_

/** @brief �V�[��ID */
enum SceneId
{
	TitleScene,			//!< �^�C�g���V�[��
	HelpScene,			//!< �w���v�V�[��
	SelectScene,		//!< �Z���N�g�V�[��
	GameScene,			//!< �Q�[���{�҃V�[��	
	GameEndScene,		//!< �Q�[���G���h�V�[��
	SceneIdMax,			//!< �V�[��ID�ő�

};

/** @brief �V�[���X�e�b�v */
enum SceneStep
{
	InitStep,			//!< ������
	MainStep,			//!< ���C��
	EndStep,			//!< �I��
};

/** @brief ���ݎ��s���̃V�[��ID�̎擾�֐� */
SceneId GetCurrentSceneId();

/** @brief ���ݎ��s���̃V�[���X�e�b�v�̎擾�֐� */
SceneStep GetCurrentSceneStep();

/**
* @brief �V�[���X�e�b�v�ύX�֐�@n
* �����Ŏw�肵���X�e�b�v�ɐ؂�ւ���
* @param[in] next_step ���̃X�e�b�v
*/
void ChangeSceneStep(SceneStep next_step);

/**
* @brief �V�[�����s�֐�@n
* �V�[�����������s����@n
* �����Ŋe�V�[���𓮂����̂Ŏg�p�҂�UpdateTitleScene�������s����K�v�͂Ȃ�
*/
void UpdateScene();

/**
* @brief �V�[���`��֐�@n
* �V�[���̃I�u�W�F�N�g��`�悷��@n
* �����Ŋe�V�[�����̕`����s���̂Ŏg�p�҂�DrawTitleScene�������s����K�v�͂Ȃ�
*/
void DrawScene();

#endif


