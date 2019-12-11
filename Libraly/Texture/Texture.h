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
	TitleLogoTex,			//!< タイトルロゴ
	TitleStart1Tex,			//!< スタートボタンOn
	TitleStart2Tex,			//!< スタートボタンOff
	TitleContinue1Tex,		//!< 続きボタンOn
	TitleContinue2Tex,		//!< 続きボタンOff
	TitleHelp1Tex,			//!< ヘルプボタンOn
	TitleHelp2Tex,			//!< ヘルプボタンOff
	TitleTextureMax			//!< リスト最大数
};

// ヘルプシーン用リスト
enum HelpCategoryTextureList
{
	Help1Tex,		//!< ヘルプ1枚目
	Help2Tex,		//!< ヘルプ2枚目
	Help3Tex,		//!< ヘルプ3枚目
	HelpTextureMax
};

// セレクトシーン用リスト
enum SelectCategoryTextureList
{
	SelectBgTex,

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
	GamePlayer_Taiki_Tp_LeftTex,			//!<プレイヤー待機左
	GamePlayer_Taiki_Tp_RightTex,			//!<プレイヤー待機右
	GamePlayer_Jump_Tp_LeftTex,				//!<ジャンプ左
	GamePlayer_Jump_Tp_RightTex,			//!<ジャンプ右
	GamePlayer_Walk_Tp_LeftTex,				//!<歩行左
	GamePlayer_Walk_Tp_RightTex,			//!<歩行右
	GamePlayer_Attack_Tp_LeftTex,			//!<攻撃左
	GamePlayer_Attack_Tp_RightTex,			//!<攻撃右
	GamePlayer_WalkAttack_Tp_LeftTex,		//!<歩行攻撃左
	GamePlayer_WalkAttack_Tp_RightTex,		//!<歩行攻撃右
	GamePlayer_JumpAttack_Tp_LeftTex,		//!<ジャンプ攻撃左
	GamePlayer_JumpAttack_Tp_RightTex,		//!<ジャンプ攻撃右
	GamePlayer_Damage_Tp_LeftTex,			//!<ダメージ左
	GamePlayer_Damage_Tp_RightTex,			//!<ダメージ右
	GamePlayer_JumpDamage_Tp_LeftTex,		//!<ジャンプダメージ左
	GamePlayer_JumpDamage_Tp_RightTex,		//!<ジャンプダメージ右
	GamePlayer_Clear_Tp_LeftTex,			//!<クリア左
	GamePlayer_Clear_Tp_RightTex,			//!<クリア右
	GamePlayer_OpeningTex,					//!<オープニング
	GamePlayerBullet_1Tex,					//!<プレイヤーの弾1
	GamePlayerBullet_2Tex,					//!<プレイヤーの弾2
	GamePlayerBullet_3Tex,					//!<プレイヤーの弾3
	GamePlayerBullet_4Tex,					//!<プレイヤーの弾4

	/*UI用*/
	GamePlayerUi,							//!<プレイヤーHP
	GameBulletUi_RedLeft,					//!<プレイヤー弾UI
	GameBulletUi_RedCenter,					//!<プレイヤー弾UI 				
	GameBulletUi_RedRight,					//!<プレイヤー弾UI
	GameBulletUi_PinkCenter,				//!<プレイヤー弾UI
	GameBulletUi_PurpleRight,				//!<プレイヤー弾UI
	GameBulletUi_BlueLeft,					//!<プレイヤー弾UI
	GameBulletUi_BlueCenter,				//!<プレイヤー弾UI
	GameBulletUi_BlueRight,					//!<プレイヤー弾UI
	GameBulletUi_GreenCenter,				//!<プレイヤー弾UI
	GameBulletUi_YellowRight,				//!<プレイヤー弾UI
	GamePlayerHp_4Tex,						//!<プレイヤー耐久残り3
	GamePlayerHp_3Tex,						//!<プレイヤー耐久残り2
	GamePlayerHp_2Tex,						//!<プレイヤー耐久残り1
	GamePlayerHp_1Tex,						//!<プレイヤー耐久残り0
	GameEnemyUi,							//!<エネミーUIの基盤
	GameEnemySleepGauge,					//!<眠気ゲージ
	GameEnemyFatigueGauge,					//!<疲労ゲージ
	GameEnemyAutoHealGauge,					//!<自動回復ライン
	GameEnemySleepCircle,					//!<眠気円
	GameEnemyFatigueCircle,					//!<疲労円
	GameEnemyAchieveUi,						//!<敵ドロップアイテム


	/*Enemy用*/
	GameEnemy_TaikiLeft,					//!<敵待機
	GameEnemy_TaikiRight,
	GameEnemy_WalkLeft,						//!<敵歩行
	GameEnemy_WalkRight,
	GameEnemy_NeedleAttackLeft,				//!<ハリネズミ攻撃
	GameEnemy_NeedleAttackRight,
	GameEnemy_DashAttackLeft,				//!<ダッシュ攻撃
	GameEnemy_DashAttackRight,
	GameEnemy_SleepLeft,					//!<敵睡眠
	GameEnemy_SleepRight,
	GameEnemy_FatigueLeft,					//!<敵疲労
	GameEnemy_FatigueRight,
	GameEnemy_DownLeft,						//!<敵死亡
	GameEnemy_DownRight,
	GameEnemy_Bullet_Needle,				//!<敵の弾(ハリ)

	GamePointerTex,			//!< ポインタ
	GameTextureMax,			//!< リスト最大数
};


/** @brief エンド用テクスチャリスト */
enum GameEndCategoryTextureList
{
	GameEndBgTex,				//!< 背景
	GameEndBlackTex,
	GameEndBloodTex,
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

