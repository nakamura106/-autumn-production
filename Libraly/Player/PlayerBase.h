#pragma once



#include"../Object/Definition.h"
#include"../Object/ObjectBase.h"

class PlayerBase :public ObjectBase
{
public:
	PlayerBase();
	~PlayerBase();
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void P_Controll() = 0;
	virtual void InitAnimation()=0;
	virtual void InitWaitAnimation() = 0;
	virtual void InitMoveAnimation() = 0;
	virtual void InitJumpAnimation() = 0;
	virtual void InitThinkAnimation() = 0;
	virtual void InitDeathAnimation() = 0;
	virtual void InitClearAnimation() = 0;
	virtual void InitDamageAnimation() = 0;
	virtual void WaitAnimation() = 0;
	virtual void MoveAnimation() = 0;
	virtual void JumpAnimation() = 0;
	virtual void ThinkAnimation() = 0;
	virtual void DeathAnimation() = 0;
	virtual void ClearAnimation() = 0;
	virtual void DamageAnimation() = 0;
	virtual Position GetPos() = 0;


protected:
	int		m_hp;				//‘Ì—Í
	UVANIMATION wait_animation_Right[12];
	UVANIMATION wait_animation_Left[12];
	UVANIMATION move_animation_Right[12];
	UVANIMATION move_animation_Left[12];
	UVANIMATION jump_animation_Right[12];
	UVANIMATION jump_animation_Left[12];
	UVANIMATION jump_attack_animation_Right[12];
	UVANIMATION jump_attack_animation_Left[12];
	UVANIMATION jump_damege_animation_Right[12];
	UVANIMATION jump_damege_animation_Left[12];
	UVANIMATION think_animation_Right[12];
	UVANIMATION think_animation_Left[12];
	UVANIMATION death_animation_Right[12];	//!–¢
	UVANIMATION death_animation_Left[12];	//!–¢
	UVANIMATION opening_animation[12];
	UVANIMATION clear_animation_Right[12];
	UVANIMATION clear_animation_Left[12];
	UVANIMATION damage_animation_Right[12];
	UVANIMATION damage_animation_Left[12];
	
};