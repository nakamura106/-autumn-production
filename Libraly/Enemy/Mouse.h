#pragma once
#include "EnemyBase.h"


/*
typedef enum AttackRepertoryofHedgeHog
{
	Rush,		//突進
	HeadButt,	//頭突き
	NeedleFire,	//トゲ発射
	None,		//何もなし
	AttackRepertoryMax,

}EnemyAttackRepertory;
*/

class HedgeHog :public EnemyBase
{
public:
	/*
	void Init();
	void Create();
	void Update();
	void Draw();
	*/

	void EnemyAttack();

protected:
	bool m_is_speed_up;		//加速するか	
	AttackRepertoryofHedgeHog m_attack_repertory;

public:
	HedgeHog();
	~HedgeHog();

	void Headbutt();

	void Rush();

	void NeedleFire();

};