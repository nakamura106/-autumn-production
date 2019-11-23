#pragma once

#pragma once

#include"PlayerBase.h"

class TrpPlayer :public PlayerBase
{
public:
	TrpPlayer();
	~TrpPlayer();

	void Init();
	void Load();
	void Create();
	void Update();
	void Draw();
	void P_Controll();
	void InitAnimation();
	void InitWaitAnimation();
	void InitMoveAnimation();
	void InitJumpAnimation();
	void InitThinkAnimation();
	void InitDeathAnimation();
	void InitClearAnimation();
	void InitDamageAnimation();
	void WaitAnimation();
	void MoveAnimation();
	void JumpAnimation();
	void ThinkAnimation();
	void DeathAnimation();
	void ClearAnimation();
	void DamageAnimation();
	Position GetPos();

private:
	
};

