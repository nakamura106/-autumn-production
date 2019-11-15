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
	int m_hp;				//ÌÍ
	int m_direction;		//ü«
	int m_state;			//vC[ÌóÔ
	int m_flamecount;		//t[JEg(UVXN[p)
	float m_centerX;		//æÌXS
	float m_centery;		//æÌYS
	float m_sprite_width;	//æÌ¡
	float m_sprite_height;	//æÌc
	float m_range;			//Ëö£
	bool m_is_invincible;	//³GÔ
	
	
};
