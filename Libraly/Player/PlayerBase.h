#pragma once



#include"../Object/Definition.h"
#include"../Object/ObjectBase.h"
#include"../Engine/Texture.h"

class PlayerBase :public ObjectBase
{
public:
	PlayerBase();
	~PlayerBase();
	//!< 初期化関数
	virtual void Init() = 0;

	void Create();
	//!< 画像読込用関数(ゲームシーンにべた書き予定)
	virtual void Load() = 0;
	//!< アップデート関数(処理更新用)
	virtual void Update() = 0;
	//!< 描画関数(オブジェクトベースでまとめてやる予定)
	virtual void Draw() = 0;
	//!< プレイヤーコントロール関数(プレイヤーの操作)
	virtual void P_Controll() = 0;
	//!< アニメーションの初期化関数
	virtual void InitAnimation()=0;
	//!< アニメーションの描画関数(画像をアニメーションさせるための関数)
	virtual void DrawAnimation() = 0;
	//!< アニメーションのアップデート関数(状態によってアニメーションを変える関数 ※DrawAnimationと統合予定)
	virtual void UpdateAnimation() = 0;
	//!< プレイヤーのジャンプ処理関数
	virtual void Jump() = 0;
	//!< 弾が射程距離を超えたら音符ストックを消す関数
	virtual void ReleaseNote() = 0;
	//!< 画像を呼び出して変数(Drawで使う)に格納する関数
	virtual void GetMotion(int Llist, int Rlist)=0;
	//!< 現在の座標を渡す関数
	virtual Position GetPos() = 0;


protected:
	bool	m_do_jump;						//ジャンプ判定
	bool	m_is_active;					//動いているかの判定
	bool	m_play_note[6];					//音符生成
	int		m_hp;							//体力
	int		m_List;							//テクスチャーリスト保存用
	int		m_Key;							//長調か短調か
	int     m_i;							//アニメーション切り替え用
	float	m_map_pos;						//マップ中央固定用



	UVANIMATION Animation[MaxAnimationNum];	//アニメーションのスプリット保存用

	UVANIMATION clear_animation_Right[12];	//アニメーションの枚数が違うので放置
	UVANIMATION clear_animation_Left[12];	//同文
};