#pragma once

#pragma once

#include"../Object/Definition.h"
#include"../Object/ObjectBase.h"

class PlayerBase :public ObjectBase
{
public:
	PlayerBase();
	~PlayerBase();
	virtual void Init() = 0;
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	int m_hp;				//体力
	int m_direction;		//向き
	int m_state;			//プレイヤーの状態
	int m_flamecount;		//フレームカウント(UVスクロール用)
	float m_centerX;		//画像のX中心
	float m_centery;		//画像のY中心
	float m_sprite_width;	//画像の横幅
	float m_sprite_height;	//画像の縦幅
	float m_range;			//射程距離
	bool m_is_invincible;	//無敵時間
	
	
};
