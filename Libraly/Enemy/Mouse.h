#pragma once
#include "EnemyBase.h"


/*
typedef enum AttackRepertoryofHedgeHog
{
	Rush,		//�ːi
	HeadButt,	//���˂�
	NeedleFire,	//�g�Q����
	None,		//�����Ȃ�
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
	bool m_is_speed_up;		//�������邩	
	AttackRepertoryofHedgeHog m_attack_repertory;

public:
	HedgeHog();
	~HedgeHog();

	void Headbutt();

	void Rush();

	void NeedleFire();

};