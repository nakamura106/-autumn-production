#pragma once


#include"PlayerBase.h"

TrpPlayer player;

class TrpPlayer :public PlayerBase
{
public:
	TrpPlayer();
	~TrpPlayer();
	 //!< 初期化関数
	 void Init()override;
	 //!< アップデート関数(処理更新用)
	 void Update()override;
	 //!< 描画関数(オブジェクトベースでまとめてやる予定)
	 void Draw()override;
	 //!< 現在の座標を渡す関数
	 Position GetPos(int select)override;
private:
	//!< プレイヤーのジャンプ処理関数
	void Jump()override;
	//!< 画像を呼び出して変数(Drawで使う)に格納する関数
	void GetMotion(int Llist, int Rlist);
	//!< アニメーションのアップデート関数(状態によってアニメーションを変える関数 ※DrawAnimationと統合予定)
	void UpdateAnimation()override;
	//!< 弾が射程距離を超えたら音符ストックを消す関数
	void ReleaseNote()override;
	//!< アニメーションの描画関数(画像をアニメーションさせるための関数)
	void DrawAnimation()override;
	//!< アニメーションの初期化関数
	void InitAnimation()override;
	//!< プレイヤーコントロール関数(プレイヤーの操作)
	void P_Controll()override;
	//!< 画像読込用関数(ゲームシーンにべた書き予定)
	void Load()override;
};

