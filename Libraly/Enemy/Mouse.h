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
	HedgeHog();
	~HedgeHog();
	
	void Init();
	//void Update();
	

private:
	bool m_is_speed_up;		//加速するか	
	AttackRepertoryofHedgeHog m_attack_repertory;

	/*待機状態からの遷移*/
	EnemyStateType ChangeStateFromWait();
	/*移動状態からの遷移*/
	EnemyStateType ChangeStateFromWalk();
	/*逃走状態からの遷移*/
	EnemyStateType ChangeStateFromRefuge();
	/*攻撃状態からの遷移*/
	EnemyStateType ChangeStateFromAttack();
	/*追跡状態からの遷移*/
	EnemyStateType ChangeStateFromChase();

	void EnemyAttack();

	void Headbutt();

	void Rush();

	void NeedleFire();


};