#pragma once
#include "EnemyBase.h"

//!~

typedef enum AttackRepertoryofHedgeHog
{
	Rush,		//“Ëi
	HeadButt,	//“ª“Ë‚«
	NeedleFire,	//ƒgƒQ”­Ë
	None,		//‰½‚à‚È‚µ
	AttackRepertoryMax,
}EnemyAttackRepertory;

//~!

class HedgeHog :public EnemyBase
{
public:
	void Init();
	void Create();
	void Update();
	void Draw();

	void EnemyAttack();

protected:
	bool m_is_speed_up;		//‰Á‘¬‚·‚é‚©		

public:
	HedgeHog();
	~HedgeHog();

	void Headbutt();

	void Rush();

	void NeedleFire();

};