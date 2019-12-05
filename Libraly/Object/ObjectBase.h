#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_
#include"../Engine/Graphics.h"

#include "Definition.h"
#include "../Texture/Texture.h"

class ObjectBase {
public:
	ObjectBase();
	~ObjectBase();

	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Update() = 0;
	virtual void Draw();

	//座標ゲッター
	Position GetPos() { return m_pos; }
	//削除判定ゲッター
	bool GetIsDelete() { return m_is_delete; }

protected:
	/*統合画像のアニメーション用関数*/
	void AnimationUpdate();
	/*アニメーション進行ゲッター*/
	int GetAnimationTexNum();

	Position		m_pos;			//座標
	DrawParam		m_draw_param;	//描画用構造体
	AnimationParam	m_anim_param;	//アニメーション用構造体

	int m_direction;		//向き(enum Directionを使用)
	bool m_is_delete;		//削除判定用
	bool m_is_invincible;	//無敵状態
	int m_state;			//状態
	float m_speed;			//移動速度

	//デバッグ用変数(12/2田中追加)
	int m_animation_timer;
	bool m_animation_end;	//アニメーションの最後かどうか
	
};

#endif

