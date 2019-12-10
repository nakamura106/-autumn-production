#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_
#include"../Engine/Graphics.h"

#include "Definition.h"
#include "../Texture/Texture.h"

class ObjectBase {
public:
	ObjectBase();
	ObjectBase(ObjectRavel obj_ravel_, Direction direction_, float speed_);
	~ObjectBase();

	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Update();
	virtual void Draw();

	//座標ゲッター
	Position GetPos() { return m_pos; }
	//削除判定ゲッター
	bool GetIsDelete() { return m_is_delete; }


	float GetHitUseAtk() { return m_hit_use_atk; }

	float GetMapPos() { return m_map_pos; };


	ObjectRavel GetRavel();	// ラベル入手

	HitRectangle GetRectParam();

	//12/10　即席当たり判定結果通知関数
	virtual void HitAction(ObjectRavel ravel_,float hit_use_atk_){}

protected:
	/*統合画像のアニメーション用関数*/
	void AnimationUpdate();
	/*アニメーション進行ゲッター*/
	int GetAnimationTexNum();

	ObjectRavel		m_obj_ravel;	//ラベル
	Position		m_pos;			//座標
	DrawParam		m_draw_param;	//描画用構造体
	AnimationParam	m_anim_param;	//アニメーション用構造体
	HitRectangle	m_rect_param;	//当たり判定用構造体

	int m_direction;		//向き(enum Directionを使用)
	bool m_is_delete;		//削除判定用
	bool m_is_invincible;	//無敵状態
	int m_state;			//状態
	float m_speed;			//移動速度


	float m_hit_use_atk;	//当たり判定時に使用する攻撃力

	float	m_map_pos;						//マップ中央固定用


	//デバッグ用変数(12/2田中追加)
	int m_animation_timer;
	bool m_animation_end;	//アニメーションの最後かどうか

	virtual void SetRectangle();	// 当たり判定構造体パラメータ設定関数　後で消す
	
};

#endif

