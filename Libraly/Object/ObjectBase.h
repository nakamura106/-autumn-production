	#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_
#include"../Engine/Graphics.h"

#include "../Effect/EffectBase.h"
#include "Definition.h"
#include "../Texture/Texture.h"
#include "../Collision/ShapeBase.h"

#include <vector>
#include <list>

class EffectBase;

class ObjectBase {
public:
	ObjectBase();
	ObjectBase(ObjectRavel obj_ravel_, Direction direction_, float speed_, int draw_angle_);
	ObjectBase(
		float pos_x_,
		float pos_y_,
		float size_x_,
		float size_y_,
		int tex_split_w_,
		int tex_split_h_,
		int tex_split_all,
		ObjectRavel obj_ravel_, 
		Direction direction_, 
		float speed_, 
		int draw_angle_, 
		bool is_turn_
	);
	~ObjectBase();

	virtual void Init() = 0;
	
	virtual void Update();
	virtual void Draw();

	/*		ゲッター		*/
	/*座標ゲッター*/
	Position GetPos() { return m_pos; }
	/*削除判定ゲッター*/
	bool GetIsDelete() { return m_is_delete; }
	/*当たり判定時に使用する値を返す*/
	float GetHitUseAtk() { return m_hit_use_atk; }

	/*当たり判定時に使用する値を返す：NewVer 1/23*/
	/*
		当たったオブジェクトを渡すことでそのオブジェクトに応じた値を返す
		(オーバーライドして各オブジェクトが設定)
	
	*/
	virtual float GetHitUseAtk(ObjectRavel hit_obj_) {
		return m_hit_use_atk;
	}

	/*マップ上の座標(ワールド座標)を返す*/
	float GetMapPos() { return m_map_pos; };
	/*Objectラベルゲッター*/
	ObjectRavel GetRavel(){ return m_obj_ravel; }
	/*当たり判定用構造体ゲッター*/
	HitRectangle GetRectParam(){ return m_rect_param; }

	//プレイヤー専用中心ゲッター
	Position GetPlayerCenter();

	//縦横の画像切り抜きサイズが同じ場合
	Position GetCenter(float splitsize_);

	//縦横の画像切り抜きサイズが違う場合
	Position GetCenter(float splitsizeX_,float splitsizeY_);

	int GetDirection() { return m_direction; }

	//12/10　即席当たり判定結果通知関数
	virtual void HitAction(ObjectRavel ravel_,float hit_use_atk_){}

	/*アニメーション進行ゲッター*/
	int GetAnimationTexNum();

	// 当たり判定リストのゲッター　collisionmanagerで使用
	std::list<ShapeBase*> GetShapeList() { return m_shape_list; }

	// Collision用Updateまとめ関数
	virtual void CollisionParamUpdate(){}

private:

protected:

	/*統合画像のアニメーション用関数*/
	void AnimationUpdate();

	/*マップの動きに合わせて位置調整*/
	void CalcDrawPosition();

	/*当たり判定構造体パラメータ設定関数　後で消す*/
	virtual void SetRectangle();

	/*地面にいるかどうかの判定*/
	bool CheckLandGround();

	/*		構造体変数		*/
	Position		m_pos;			//座標
	Position		m_P_Center;
	Position		m_Tex_Center;
	DrawParam		m_draw_param;	//描画用構造体
	AnimationParam	m_anim_param;	//アニメーション用構造体
	HitRectangle	m_rect_param;	//当たり判定用構造体

	/*		単体変数群		*/
	ObjectRavel	m_obj_ravel;		//ラベル
	int			m_direction;		//向き(enum Directionを使用)
	bool		m_is_delete;		//削除判定用
	bool		m_is_invincible;	//無敵状態
	int			m_state;			//状態
	float		m_speed;			//移動速度
	float		m_hit_use_atk;		//当たり判定時に使用する攻撃力
	float		m_map_pos;			//マップ中央固定用
	int			m_animation_timer;	//アニメーションタイマー
	bool		m_is_animation_end;	//アニメーションの最後かどうか
	int			m_draw_angle;		//描画する角度
	bool		m_is_turn;			//画像反転させるかどうか

	std::vector<EffectBase*> m_effect_list;	// エフェクト保存用配列
	std::list<ShapeBase*> m_shape_list;// 当たり判定用リスト
};

#endif

