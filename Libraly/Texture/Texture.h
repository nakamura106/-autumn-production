/**
* @file Texture.h
* @brief �e�N�X�`���̓ǂݍ��݁A����ȂǁA�e�N�X�`���Ɋւ���֐��A�萔�̐錾
*/
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../Scene/Scene.h"
#include "../Engine/Graphics.h"

/** @brief �^�C�g���p�e�N�X�`���̃��X�g */
enum TitleCategoryTextureList
{
	TitleBgTex,				//!< �w�i
	TitleMenuGoGameTex,		//!< �Q�[���J��
	TitleMenuGoHelpTex,		//!< �w���v�J��
	TitleMenuGoGameOnTex,	//!< �Q�[���J�ځiOnMouse.Ver�j	
	TitleBombTex,			//!< �{�����T���v��
	TitleMenuGoBackTex,
	TitleMenuGoBackOnTex,
	TitleTextureMax			//!< ���X�g�ő吔
};

/** @brief �Q�[���{�җp�e�N�X�`���̃��X�g */
enum GameCategoryTextureList
{
	GameBgTex,								//!<�w�i
	GamefloorTex,							//!<��
	Gamefloor2Tex,							//!<��2
	GameFgTex,								//!<�ߌi
	GameObject,								//!< �t���[
	GameObject2,							//!< �t���[
	GameObject3,							//!< �t���[
	GameObject4,							//!< �t���[
	GameObject5,							//!< �t���[
	GamePlayer_Taiki_Tp_LeftTex,			//!<�v���C���[�ҋ@��
	GamePlayer_Taiki_Tp_RightTex,			//!<�v���C���[�ҋ@�E
	GamePlayer_Jump_Tp_LeftTex,				//!<�W�����v��
	GamePlayer_Jump_Tp_RightTex,			//!<�W�����v�E
	GamePlayer_Walk_Tp_LeftTex,				//!<���s��
	GamePlayer_Walk_Tp_RightTex,			//!<���s�E
	GamePlayer_Attack_Tp_LeftTex,			//!<�U����
	GamePlayer_Attack_Tp_RightTex,			//!<�U���E
	GamePlayer_WalkAttack_Tp_LeftTex,		//!<���s�U����
	GamePlayer_WalkAttack_Tp_RightTex,		//!<���s�U���E
	GamePlayer_JumpAttack_Tp_LeftTex,		//!<�W�����v�U����
	GamePlayer_JumpAttack_Tp_RightTex,		//!<�W�����v�U���E
	GamePlayer_Damage_Tp_LeftTex,			//!<�_���[�W��
	GamePlayer_Damage_Tp_RightTex,			//!<�_���[�W�E
	GamePlayer_JumpDamage_Tp_LeftTex,		//!<�W�����v�_���[�W��
	GamePlayer_JumpDamage_Tp_RightTex,		//!<�W�����v�_���[�W�E
	GamePlayer_Clear_Tp_LeftTex,			//!<�N���A��
	GamePlayer_Clear_Tp_RightTex,			//!<�N���A�E
	GamePlayer_OpeningTex,					//!<�I�[�v�j���O
	GameBoss_TaikiTex,						//!<�G�ҋ@
	GameBoss_WalkTex,						//!<�G���s
	GameBoss_Needle_AttackTex,				//!<�n���l�Y�~�U��
	GameBoss_SleepTex,						//!<�G����
	GameBoss_Fatigue,						//!<�G��J
	GamePointerTex,			//!< �|�C���^
	GameTextureMax,			//!< ���X�g�ő吔
};




/** @brief �w���v�p�e�N�X�`�����X�g */
enum GameEndCategoryTextureList
{
	GameEndBgTex,				//!< �w�i
	GameEndBlackTex,
	GameEndBloodTex,
	GameEndTextureMax,			//!< ���X�g�ő吔
};

#define TEXTURE_CATEGORY_TITLE (SceneId::TitleScene)			//!< �^�C�g���J�e�S���[
#define TEXTURE_CATEGORY_GAME (SceneId::GameScene)				//!< �Q�[���{�҃J�e�S���[
#define TEXTURE_CATEGORY_GAMEEND (SceneId::GameEndScene)				//!< �G���h�J�e�S���[
#define MAX_TEXTURE_CATEGORY (SceneId::SceneIdMax)				//!< �J�e�S���[�ő�

/**
* @brief �e�N�X�`���f�[�^�������֐�@n
* �Q�[���Ŏg�p����e�N�X�`���f�[�^��ۑ��o����悤�ɂ���
*/
void InitTexture();

/**
* @brief �J�e�S���[�P�ʂ̃e�N�X�`������֐�@n
* �����Ŏw�肳�ꂽ�J�e�S���[�̃e�N�X�`����S�ĉ������
* @param[in] category_id ����J�e�S���[
*/
void ReleaseCategoryTexture(int category_id);

/**
* @brief �e�N�X�`���̑S���@n
* �ǂݍ���ł��邷�ׂẴe�N�X�`�����������@n
* �����̊֐���EndEngine�Ŏg�p����Ă���̂ŊJ�����ŌĂԕK�v�͂Ȃ�
*/
void AllReleaseTexture();

/**
* @brief �e�N�X�`���̓ǂݍ���@n
* �w�肵�����ꂽ�p�X�̃e�N�X�`����ǂݍ��݁A�J�e�S���ɓo�^����
* @return �ǂݍ��݌���(������true)
* @param[in] file_name �ǂݍ��ރe�N�X�`����(�p�X����)
* @param[in] category_id �o�^����J�e�S���[
* @param[in] texture_id �J�e�S���[���̃e�N�X�`��ID
*/
bool LoadTexture(const char* file_name, int category_id, int texture_id);

/**
* @brief �e�N�X�`���f�[�^�̎擾@n
* �w�肳�ꂽ�J�e�S���̃e�N�X�`���f�[�^���擾����
* @return �e�N�X�`���f�[�^(�擾���s����nullptr)
* @param[in] �擾�������e�N�X�`���̃J�e�S��
* @param[in] �擾�������e�N�X�`����ID
*/
Texture* GetTexture(int category_id, int texture_id);

#endif

