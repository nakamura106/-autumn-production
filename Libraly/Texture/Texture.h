/**
* @file Texture.h
* @brief テクスチャの読み込み、解放など、テクスチャに関する関数、定数の宣言
*/
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../Scene/Scene.h"
#include "../Engine/Graphics.h"

/** @brief タイトル用テクスチャのリスト */
enum TitleCategoryTextureList
{
	TitleBgTex,				//!< 背景
	TitleMenuGoGameTex,		//!< ゲーム遷移
	TitleMenuGoHelpTex,		//!< ヘルプ遷移
	TitleMenuGoGameOnTex,	//!< ゲーム遷移（OnMouse.Ver）	
	TitleBombTex,			//!< ボム兵サンプル
	TitleMenuGoBackTex,
	TitleMenuGoBackOnTex,
	TitleTextureMax			//!< リスト最大数
};

/** @brief ゲーム本編用テクスチャのリスト */
enum GameCategoryTextureList
{
	GameBgTex,				//!< 背景
	GameObject,				//!< フリー
	GameObject2,				//!< フリー
	GameObject3,				//!< フリー
	GameObject4,				//!< フリー
	GameObject5,				//!< フリー
	GameObject6,				//!< フリー
	GameObject7,				//!< フリー
	GameObject8,				//!< フリー
	GameObject9,				//!< フリー
	GameObject10,				//!< フリー
	GameObject11,				//!< フリー
	GameObject12,				//!< フリー
	GameObject13,				//!< フリー
	GameObject14,				//!< フリー
	GameObject15,				//!< フリー
	GameObject16,				//!< フリー
	GameObject17,				//!< フリー
	GameObject18,				//!< フリー
	GameObject19,				//!< フリー
	GameObject20,				//!< フリー
	GamePlayerTex,			//!< プレイヤー
	GameEnemyTex,
	GamePointerTex,			//!< ポインタ
	GameDarkTex,			//!< 透過0暗闇
	GameDarkTex2,
	GameFlashLightTex,		//!< 懐中電灯光源
	GameWallTex,			//!< 壁
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
	GameTextureMax,			//!< リスト最大数
};

/** @brief アドベンチャーパート用テクスチャのリスト */
enum AdvCategoryTextureList
{
	AdvBg1Tex, //!< 背景
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
	AdvTextureMax,		//!< リスト最大数
};

/** @brief アイテム調査パート用テクスチャのリスト */
enum ResearchCategoryTextureList
{
	ResearchBgTex,			//!< 背景
	ResearchRightTex,		//!< 右のボタン
	ResearchLeftTex,		//!< 左のボタン
	ResearchClosetTex,		//!< 洋ダンス
	ResearchTapLightTex,		//!< バッテン型ボタン
	ResearchBackMouseTex,		//!< バッテン型ボタン
	ResearchVellTex,		//!< バッテン型ボタン
	ResearchSampleTex,		//!< バッテン型ボタン
	ResearchIllustTex,		//!< バッテン型ボタン
	ResearchIllust2Tex,		//!< バッテン型ボタン
	ResearchOnBreakerTex,		//!< バッテン型ボタン
	ResearchOffBreakerTex,		//!< バッテン型ボタン
	ResearchKeyTex,		//!< バッテン型ボタン
	ResearchFlameTex,		//!< バッテン型ボタン
	ResearchFlameTapeTex,		//!< バッテン型ボタン
	ResearchKeyTapeTex,		//!< バッテン型ボタン
	ResearchFreeItem1Tex,
	ResearchFreeItem2Tex,
	ResearchFreeItem3Tex,
	ResearchFreeItem4Tex,
	ResearchFreeItem5Tex,
	ResearchTextureMax,		//!< リスト最大数
};

/** @brief ヘルプ用テクスチャリスト */
enum GameEndCategoryTextureList
{
	GameEndBgTex,				//!< 背景
	GameEndBlackTex,
	GameEndBloodTex,
	GameEndTextureMax,			//!< リスト最大数
};

#define TEXTURE_CATEGORY_TITLE (SceneId::TitleScene)			//!< タイトルカテゴリー
#define TEXTURE_CATEGORY_GAMEEND (SceneId::GameEndScene)				//!< ヘルプカテゴリー
#define TEXTURE_CATEGORY_GAME (SceneId::GameScene)				//!< ゲーム本編カテゴリー
#define TEXTURE_CATEGORY_ADV (SceneId::AdvScene)				//!< アドベンチャーパートカテゴリー
#define TEXTURE_CATEGORY_RESEARCH (SceneId::ResearchScene)		//!< アイテム調査パートカテゴリー
#define MAX_TEXTURE_CATEGORY (SceneId::SceneIdMax)				//!< カテゴリー最大

/**
* @brief テクスチャデータ初期化関数@n
* ゲームで使用するテクスチャデータを保存出来るようにする
*/
void InitTexture();

/**
* @brief カテゴリー単位のテクスチャ解放関数@n
* 引数で指定されたカテゴリーのテクスチャを全て解放する
* @param[in] category_id 解放カテゴリー
*/
void ReleaseCategoryTexture(int category_id);

/**
* @brief テクスチャの全解放@n
* 読み込んでいるすべてのテクスチャを解放する@n
* ※この関数はEndEngineで使用されているので開発側で呼ぶ必要はない
*/
void AllReleaseTexture();

/**
* @brief テクスチャの読み込み@n
* 指定したされたパスのテクスチャを読み込み、カテゴリに登録する
* @return 読み込み結果(成功はtrue)
* @param[in] file_name 読み込むテクスチャ名(パス込み)
* @param[in] category_id 登録するカテゴリー
* @param[in] texture_id カテゴリー内のテクスチャID
*/
bool LoadTexture(const char* file_name, int category_id, int texture_id);

/**
* @brief テクスチャデータの取得@n
* 指定されたカテゴリのテクスチャデータを取得する
* @return テクスチャデータ(取得失敗時はnullptr)
* @param[in] 取得したいテクスチャのカテゴリ
* @param[in] 取得したいテクスチャのID
*/
Texture* GetTexture(int category_id, int texture_id);

#endif

