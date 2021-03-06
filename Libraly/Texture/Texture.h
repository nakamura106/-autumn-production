/**
* @file Texture.h
* @brief テクスチャの読み込み、解放など、テクスチャに関する関数、定数の宣言
*/
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../Scene/Scene.h"
#include "../Engine/Graphics.h"

const float PI = 3.14159265f;

/** @brief タイトル用テクスチャのリスト */
enum TitleCategoryTextureList
{
	TitleBgTex,				//!< 背景
	TitleLogoTex,			//!< タイトルロゴ
	TitleStart1Tex,			//!< スタートボタンOn
	TitleStart2Tex,			//!< スタートボタンOff
	TitleContinue1Tex,		//!< 続きボタンOn
	TitleContinue2Tex,		//!< 続きボタンOff
	TitleHelp1Tex,			//!< ヘルプボタンOn
	TitleHelp2Tex,			//!< ヘルプボタンOff
	Help1Tex,				//!< ヘルプ画面で使う素材
	Help2Tex,
	Help3Tex,
	TitleTextureMax			//!< リスト最大数
};

// ヘルプシーン用リスト
enum HelpCategoryTextureList
{
	HelpBgTex,
	HelpTextureMax
};

// セレクトシーン用リスト
enum SelectCategoryTextureList
{
	SelectBgTex,
	BossSelectBottonTex,
	BrassSelectBottonTex,
	ClearSymbolTex,
	CompleteSymbolTex,
	BossMouseImageTex,
	BossBirdImageTex,
	BossGorillaImageTex,
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

/** @brief ゲーム本編用テクスチャのリスト */
enum GameCategoryTextureList
{
GameBgTex,								//!<背景
GamefloorTex,							//!<床
Gamefloor2Tex,							//!<床2
GameFgTex,								//!<近景
GameObject,								//!< 草1
GameObject2,							//!< 草２
GameObject3,							//!< 草３
GameObject4,							//!< フリー
GameObject5,							//!< フリー
GamePlayer_Taiki_LeftTex,			//!<プレイヤー待機左
GamePlayer_Taiki_RightTex,			//!<プレイヤー待機右
GamePlayer_Jump_LeftTex,				//!<ジャンプ左
GamePlayer_Jump_RightTex,			//!<ジャンプ右
GamePlayer_Walk_LeftTex,				//!<歩行左
GamePlayer_Walk_RightTex,			//!<歩行右
GamePlayer_Attack_LeftTex,			//!<攻撃左
GamePlayer_Attack_RightTex,			//!<攻撃右
GamePlayer_WalkAttack_LeftTex,		//!<歩行攻撃左
GamePlayer_WalkAttack_RightTex,		//!<歩行攻撃右
GamePlayer_JumpAttack_LeftTex,		//!<ジャンプ攻撃左
GamePlayer_JumpAttack_RightTex,		//!<ジャンプ攻撃右
GamePlayer_Damage_LeftTex,			//!<ダメージ左
GamePlayer_Damage_RightTex,			//!<ダメージ右
GamePlayer_JumpDamage_LeftTex,		//!<ジャンプダメージ左
GamePlayer_JumpDamage_RightTex,		//!<ジャンプダメージ右
GamePlayer_Clear_LeftTex,			//!<クリア左
GamePlayer_Clear_RightTex,			//!<クリア右
GamePlayer_OpeningTex,					//!<オープニング
GamePlayerBullet_1Tex,					//!<プレイヤーの弾1
GamePlayerBullet_2Tex,					//!<プレイヤーの弾2
GamePlayerBullet_3Tex,					//!<プレイヤーの弾3
GamePlayerBullet_4Tex,					//!<プレイヤーの弾4

/*UI用*/
GamePlayerUi,					//!<プレイヤーHP
GameBulletUi_RedLeft,			//!<プレイヤー弾UI
GameBulletUi_RedCenter,			//!<プレイヤー弾UI 				
GameBulletUi_RedRight,			//!<プレイヤー弾UI
GameBulletUi_PinkCenter,		//!<プレイヤー弾UI
GameBulletUi_PurpleRight,		//!<プレイヤー弾UI
GameBulletUi_BlueLeft,			//!<プレイヤー弾UI
GameBulletUi_BlueCenter,		//!<プレイヤー弾UI
GameBulletUi_BlueRight,			//!<プレイヤー弾UI
GameBulletUi_GreenCenter,		//!<プレイヤー弾UI
GameBulletUi_YellowRight,		//!<プレイヤー弾UI
GamePlayerHp_4Tex,				//!<プレイヤー耐久残り3
GamePlayerHp_3Tex,				//!<プレイヤー耐久残り2
GamePlayerHp_2Tex,				//!<プレイヤー耐久残り1
GamePlayerHp_1Tex,				//!<プレイヤー耐久残り0
GamePlayerBrassUi1,				//!トランペットUI
GamePlayerBrassUi2,				//!<フルートUI
GamePlayerBrassUi3,				//!<チューバUI
GameEnemyUi,					//!<エネミーUIの基盤
GameEnemyUi1,
GameEnemyUi2,
GameEnemySleepGauge,			//!<眠気ゲージ
GameEnemyFatigueGauge,			//!<疲労ゲージ
GameEnemyGaugeBase,				//!<ライフゲージの一番下
GameEnemyAutoHealGauge,			//!<自動回復ライン
GameEnemySleepCircle,			//!<眠気円
GameEnemyFatigueCircle,			//!<疲労円
GameEnemyAchieveUi,				//!<敵ドロップアイテム
GameLifeBarCut1,				
GameLifeBarCut2,


/*Enemy用*/
GameEnemy_WaitLeft,			//!<敵待機
GameEnemy_WaitRight,
GameEnemy_SkyWaitLeft,
GameEnemy_SkyWaitRight,
GameEnemy_WalkLeft,				//!<敵歩行
GameEnemy_WalkRight,
GameEnemy_Attack2Left,			//!<攻撃1
GameEnemy_Attack2Right,
GameEnemy_Attack1Left,			//!<攻撃2
GameEnemy_Attack1Right,
GameEnemy_Attack3Left,			//!<攻撃3
GameEnemy_Attack3Right,
GameEnemy_SleepLeft,			//!<敵睡眠
GameEnemy_SleepRight,
GameEnemy_FatigueLeft,			//!<敵疲労
GameEnemy_FatigueRight,
GameEnemy_DownLeft,				//!<敵死亡
GameEnemy_DownRight,
GameEnemy_FlappingLeft,			//!<敵羽ばたき
GameEnemy_FlappingRight,
GameEnemy_Attack4Left,			//!<攻撃4
GameEnemy_Attack4Right,

GameEnemy_Bullet_Normal,		//!<敵の弾(ハリ)
GameEnemy_Bullet_Shit,			//!<敵の弾(フン)
GameEnemy_Bullet_Inpact,		//!<敵の弾(衝撃波)

Game_NowLoading,

/* エフェクト用 */
GameDebuffEffect,		//!< デバフエフェクト
GameDieEffect,			//!< 死亡エフェクト
GameFailureEffect,		//!< 演奏失敗エフェクト
GameHitEffect,			//!< 攻撃ヒットエフェクト
GameItemDropEffect,		//!< アイテムドロップエフェクト
GameLandingEffect,		//!< 着地エフェクト
GameShotEffect,			//!< 被弾エフェクト
GameSleepEffect,		//!< 睡眠時エフェクト
GameSweatEffect,		//!< 残りHP１時エフェクト

GamePointerTex,			//!< ポインタ
GameTextureMax,			//!< リスト最大数
GameTextureNone = GameTextureMax,
};


/** @brief エンド用テクスチャリスト */
enum GameEndCategoryTextureList
{
	GameClearBgTex,				//!< 背景
	GameOverBgTex,
	GameOverRTex,
	GameBuckTex,
	GameEndTextureMax,			//!< リスト最大数
};

#define TEXTURE_CATEGORY_TITLE (SceneId::TitleScene)			//!< タイトルカテゴリー
#define TEXTURE_CATEGORY_HELP (SceneId::HelpScene)				//!< ヘルプシーン
#define TEXTURE_CATEGORY_SELECT (SceneId::SelectScene)			//!< セレクトシーン
#define TEXTURE_CATEGORY_GAME (SceneId::GameScene)				//!< ゲーム本編カテゴリー
#define TEXTURE_CATEGORY_GAMEEND (SceneId::GameEndScene)				//!< エンドカテゴリー
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

