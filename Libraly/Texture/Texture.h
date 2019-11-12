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
	GameBgTex,				//!< �w�i
	GameObject,				//!< �t���[
	GameObject2,				//!< �t���[
	GameObject3,				//!< �t���[
	GameObject4,				//!< �t���[
	GameObject5,				//!< �t���[
	GameObject6,				//!< �t���[
	GameObject7,				//!< �t���[
	GameObject8,				//!< �t���[
	GameObject9,				//!< �t���[
	GameObject10,				//!< �t���[
	GameObject11,				//!< �t���[
	GameObject12,				//!< �t���[
	GameObject13,				//!< �t���[
	GameObject14,				//!< �t���[
	GameObject15,				//!< �t���[
	GameObject16,				//!< �t���[
	GameObject17,				//!< �t���[
	GameObject18,				//!< �t���[
	GameObject19,				//!< �t���[
	GameObject20,				//!< �t���[
	GamePlayerTex,			//!< �v���C���[
	GameEnemyTex,
	GamePointerTex,			//!< �|�C���^
	GameDarkTex,			//!< ����0�È�
	GameDarkTex2,
	GameFlashLightTex,		//!< �����d������
	GameWallTex,			//!< ��
	GameMapBlackTex,
	GameMapWall1Tex,
	GameMapWall2Tex,
	GameMapWall3Tex,
	GameMapWall4Tex,
	GameMapFloor1Tex,
	GameMapFloor2Tex,
	GameMapFloor3Tex,
	GameMapFloor4Tex,
	GameMapVellTex,
	GameMapButton1Tex,
	GameFloorVell1Tex,
	GameFloorVell2Tex,
	GameBookshelfTex,
	GameBloodTex,
	GameBlood2Tex,
	GameExMarkTex,
	GameExitMarkTex,
	GameMarkTex,
	GameClosetTex,
	GameDishTex,
	GameSyoujoTex,
	GameSyujinkoTex,
	GameMapStarTex,
	GameTextureMax,			//!< ���X�g�ő吔
};

/** @brief �A�h�x���`���[�p�[�g�p�e�N�X�`���̃��X�g */
enum AdvCategoryTextureList
{
	AdvBg1Tex, //!< �w�i
	AdvBg2Tex,
	AdvBg3Tex,
	AdvBg4Tex,
	AdvBgBlackTex,
	AdvGirlDirtyTex,
	AdvGirlNormalTex,
	AdvGirlHappyTex,
	AdvGirlAngryTex,
	AdvGirlSadTex,
	AdvGirlSurpriseTex,
	AdvGirlThinkTex,
	AdvGirlSad2Tex,
	AdvPlayerNormalTex,
	AdvPlayerHappyTex,
	AdvPlayerAngryTex,
	AdvPlayerSadTex,
	AdvPlayerSurpriseTex,
	AdvPlayerThinkTex,
	AdvGirlShadowTex,
	AdvGirlDirtyShadowTex,
	AdvPlayerShadowTex,
	AdvWinTex,
	AdvWin2Tex,
	AdvTextureMax,		//!< ���X�g�ő吔
};

/** @brief �A�C�e�������p�[�g�p�e�N�X�`���̃��X�g */
enum ResearchCategoryTextureList
{
	ResearchBgTex,			//!< �w�i
	ResearchRightTex,		//!< �E�̃{�^��
	ResearchLeftTex,		//!< ���̃{�^��
	ResearchClosetTex,		//!< �m�_���X
	ResearchTapLightTex,		//!< �o�b�e���^�{�^��
	ResearchBackMouseTex,		//!< �o�b�e���^�{�^��
	ResearchVellTex,		//!< �o�b�e���^�{�^��
	ResearchSampleTex,		//!< �o�b�e���^�{�^��
	ResearchIllustTex,		//!< �o�b�e���^�{�^��
	ResearchIllust2Tex,		//!< �o�b�e���^�{�^��
	ResearchOnBreakerTex,		//!< �o�b�e���^�{�^��
	ResearchOffBreakerTex,		//!< �o�b�e���^�{�^��
	ResearchKeyTex,		//!< �o�b�e���^�{�^��
	ResearchFlameTex,		//!< �o�b�e���^�{�^��
	ResearchFlameTapeTex,		//!< �o�b�e���^�{�^��
	ResearchKeyTapeTex,		//!< �o�b�e���^�{�^��
	ResearchFreeItem1Tex,
	ResearchFreeItem2Tex,
	ResearchFreeItem3Tex,
	ResearchFreeItem4Tex,
	ResearchFreeItem5Tex,
	ResearchTextureMax,		//!< ���X�g�ő吔
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
#define TEXTURE_CATEGORY_GAMEEND (SceneId::GameEndScene)				//!< �w���v�J�e�S���[
#define TEXTURE_CATEGORY_GAME (SceneId::GameScene)				//!< �Q�[���{�҃J�e�S���[
#define TEXTURE_CATEGORY_ADV (SceneId::AdvScene)				//!< �A�h�x���`���[�p�[�g�J�e�S���[
#define TEXTURE_CATEGORY_RESEARCH (SceneId::ResearchScene)		//!< �A�C�e�������p�[�g�J�e�S���[
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

