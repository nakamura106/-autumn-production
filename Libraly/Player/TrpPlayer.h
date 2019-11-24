#pragma once

#pragma once

#include"PlayerBase.h"

class TrpPlayer :public PlayerBase
{
public:
	TrpPlayer();
	~TrpPlayer();

	 void Init();
	 void Load() ;
	 void Create() ;
	 void Update() ;
	 void Draw() ;
	 void P_Controll();
	 void InitAnimation() ;
	 void InitWaitAnimation() ;
	 void InitMoveAnimation() ;
	 void InitAttackAnimation() ;
	 void InitJumpAttackAnimation() ;
	 void InitJumpAnimation() ;
	 void InitThinkAnimation() ;
	 void InitDeathAnimation() ;
	 void InitClearAnimation() ;
	 void InitDamageAnimation() ;
	 void InitJumpDamageAnimation();
	 void InitOpeningAnimation() ;
	 void WaitAnimation() ;
	 void MoveAnimation() ;
	 void AttackAnimation() ;
	 void JumpAttackAnimation() ;
	 void JumpAnimation() ;
	 void ThinkAnimation();
	 void DeathAnimation() ;
	 void ClearAnimation() ;
	 void DamageAnimation();
	 void JumpDamageAnimation();
	 void OpeningAnimation() ;
	 Position GetPos();

private:
	
};

