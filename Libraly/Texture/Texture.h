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
	TitleLogoTex,			//!< �^�C�g�����S
	TitleStart1Tex,			//!< �X�^�[�g�{�^��On
	TitleStart2Tex,			//!< �X�^�[�g�{�^��Off
	TitleContinue1Tex,		//!< �����{�^��On
	TitleContinue2Tex,		//!< �����{�^��Off
	TitleHelp1Tex,			//!< �w���v�{�^��On
	TitleHelp2Tex,			//!< �w���v�{�^��Off
	TitleTextureMax			//!< ���X�g�ő吔
};

// �w���v�V�[���p���X�g
enum HelpCategoryTextureList
{
	HelpBgTex,
	Help1Tex,		//!< �w���v1����
	Help2Tex,		//!< �w���v2����
	Help3Tex,		//!< �w���v3����
	HelpTextureMax
};

// �Z���N�g�V�[���p���X�g
enum SelectCategoryTextureList
{
	SelectBgTex,
	BossSelectBottonTex,
	BrassSelectBottonTex,
	ClearSymbolTex,
	CompleteSymbolTex,
	BossMouseImageTex,
	SpotlightTex,
	TimeSymbolTex,
	NumberCollectedTex,

	BossMouseFrame1,
	BossMouseFrame2,
	BossBirdFrame1,
	BossBirdFrame2,
	BossBirdFrame3,
	BossGorillaFrame1,
	BossGorillaFrame2,
	BossGorillaFrame3,

	TrpFrame1,
	TrpFrame2,
	FluteFrame1,
	FluteFrame2,
	FluteFrame3,
	TubaFrame1,
	TubaFrame2,
	TubaFrame3,

	SelectTextureMax
};

/** @brief �Q�[���{�җp�e�N�X�`���̃��X�g */
enum GameCategoryTextureList
{
GameBgTex,								//!<�w�i
GamefloorTex,							//!<��
Gamefloor2Tex,							//!<��2
GameFgTex,								//!<�ߌi
GameObject,								//!< ��1
GameObject2,							//!< ���Q
GameObject3,							//!< ���R
GameObject4,							//!< �t���[
GameObject5,							//!< �t���[
GamePlayer_Taiki_LeftTex,			//!<�v���C���[�ҋ@��
GamePlayer_Taiki_RightTex,			//!<�v���C���[�ҋ@�E
GamePlayer_Jump_LeftTex,				//!<�W�����v��
GamePlayer_Jump_RightTex,			//!<�W�����v�E
GamePlayer_Walk_LeftTex,				//!<���s��
GamePlayer_Walk_RightTex,			//!<���s�E
GamePlayer_Attack_LeftTex,			//!<�U����
GamePlayer_Attack_RightTex,			//!<�U���E
GamePlayer_WalkAttack_LeftTex,		//!<���s�U����
GamePlayer_WalkAttack_RightTex,		//!<���s�U���E
GamePlayer_JumpAttack_LeftTex,		//!<�W�����v�U����
GamePlayer_JumpAttack_RightTex,		//!<�W�����v�U���E
GamePlayer_Damage_LeftTex,			//!<�_���[�W��
GamePlayer_Damage_RightTex,			//!<�_���[�W�E
GamePlayer_JumpDamage_LeftTex,		//!<�W�����v�_���[�W��
GamePlayer_JumpDamage_RightTex,		//!<�W�����v�_���[�W�E
GamePlayer_Clear_LeftTex,			//!<�N���A��
GamePlayer_Clear_RightTex,			//!<�N���A�E
GamePlayer_OpeningTex,					//!<�I�[�v�j���O
GamePlayerBullet_1Tex,					//!<�v���C���[�̒e1
GamePlayerBullet_2Tex,					//!<�v���C���[�̒e2
GamePlayerBullet_3Tex,					//!<�v���C���[�̒e3
GamePlayerBullet_4Tex,					//!<�v���C���[�̒e4

/*UI�p*/
GamePlayerUi,					//!<�v���C���[HP
GameBulletUi_RedLeft,			//!<�v���C���[�eUI
GameBulletUi_RedCenter,			//!<�v���C���[�eUI 				
GameBulletUi_RedRight,			//!<�v���C���[�eUI
GameBulletUi_PinkCenter,		//!<�v���C���[�eUI
GameBulletUi_PurpleRight,		//!<�v���C���[�eUI
GameBulletUi_BlueLeft,			//!<�v���C���[�eUI
GameBulletUi_BlueCenter,		//!<�v���C���[�eUI
GameBulletUi_BlueRight,			//!<�v���C���[�eUI
GameBulletUi_GreenCenter,		//!<�v���C���[�eUI
GameBulletUi_YellowRight,		//!<�v���C���[�eUI
GamePlayerHp_4Tex,				//!<�v���C���[�ϋv�c��3
GamePlayerHp_3Tex,				//!<�v���C���[�ϋv�c��2
GamePlayerHp_2Tex,				//!<�v���C���[�ϋv�c��1
GamePlayerHp_1Tex,				//!<�v���C���[�ϋv�c��0
GameEnemyUi,					//!<�G�l�~�[UI�̊��
GameEnemySleepGauge,			//!<���C�Q�[�W
GameEnemyFatigueGauge,			//!<��J�Q�[�W
GameEnemyAutoHealGauge,			//!<�����񕜃��C��
GameEnemySleepCircle,			//!<���C�~
GameEnemyFatigueCircle,			//!<��J�~
GameEnemyAchieveUi,				//!<�G�h���b�v�A�C�e��


/*Enemy�p*/
GameEnemy_WaitLeft,			//!<�G�ҋ@
GameEnemy_WaitRight,
GameEnemy_SkyWaitLeft,
GameEnemy_SkyWaitRight,
GameEnemy_WalkLeft,				//!<�G���s
GameEnemy_WalkRight,
GameEnemy_Attack2Left,			//!<�U��1
GameEnemy_Attack2Right,
GameEnemy_Attack1Left,			//!<�U��2
GameEnemy_Attack1Right,
GameEnemy_Attack3Left,			//!<�U��3
GameEnemy_Attack3Right,
GameEnemy_SleepLeft,			//!<�G����
GameEnemy_SleepRight,
GameEnemy_FatigueLeft,			//!<�G��J
GameEnemy_FatigueRight,
GameEnemy_DownLeft,				//!<�G���S
GameEnemy_DownRight,
//GameEnemy_FlyLeft,			//!<�G��s
//GameEnemy_FlyRight,
GameEnemy_FlappingLeft,			//!<�G�H�΂���
GameEnemy_FlappingRight,

GameEnemy_Bullet_Normal,		//!<�G�̒e(�n��)
GameEnemy_Bullet_Shit,			//!<�G�̒e(�t��)


/* �G�t�F�N�g�p */
GameDebuffEffect,		//!< �f�o�t�G�t�F�N�g
GameDieEffect,			//!< ���S�G�t�F�N�g
GameFailureEffect,		//!< ���t���s�G�t�F�N�g
GameHitEffect,			//!< �U���q�b�g�G�t�F�N�g
GameItemDropEffect,		//!< �A�C�e���h���b�v�G�t�F�N�g
GameLandingEffect,		//!< ���n�G�t�F�N�g
GameShotEffect,			//!< ��e�G�t�F�N�g
GameSleepEffect,		//!< �������G�t�F�N�g
GameSweatEffect,		//!< �c��HP�P���G�t�F�N�g

GamePointerTex,			//!< �|�C���^
GameTextureMax,			//!< ���X�g�ő吔
GameTextureNone = GameTextureMax,
};


/** @brief �G���h�p�e�N�X�`�����X�g */
enum GameEndCategoryTextureList
{
	GameClearBgTex,				//!< �w�i
	GameOverBgTex,
	GameOverRTex,
	GameBuckTex,
	GameEndTextureMax,			//!< ���X�g�ő吔
};

#define TEXTURE_CATEGORY_TITLE (SceneId::TitleScene)			//!< �^�C�g���J�e�S���[
#define TEXTURE_CATEGORY_HELP (SceneId::HelpScene)				//!< �w���v�V�[��
#define TEXTURE_CATEGORY_SELECT (SceneId::SelectScene)			//!< �Z���N�g�V�[��
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

