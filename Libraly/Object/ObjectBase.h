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
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw();

protected:
	Position m_pos;			//座標
	DrawParam m_param;		// 描画用構造体
	int m_direction;		//向き
	bool m_is_delete;		//削除判定用
	bool m_is_invincible;	//無敵状態
	int m_state;			//状態
	int m_flame_count;		//フレームカウント
	float m_centerX;		//X中心
	float m_centerY;		//Y中心
	float m_sprite_width;	//画像の横幅
	float m_sprite_height;	//画像の高さ
	float m_range;			//射程距離
	float m_speed;			//動く速さ
	float m_tu;
	float m_tv;

};

#endif

