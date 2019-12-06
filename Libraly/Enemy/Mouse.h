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
	HedgeHog();
	~HedgeHog();
	
	void Init();
	//void Update();
	

private:
	std::string M_AIDataFileName = "Res/Csv/Mouse/EnemyAI";
	bool m_is_speed_up;		//�������邩	
	AttackRepertoryofHedgeHog m_attack_repertory;

	/*�ҋ@��Ԃ���̑J��*/
	EnemyStateType ChangeStateFromWait();
	/*�ړ���Ԃ���̑J��*/
	EnemyStateType ChangeStateFromWalk();
	/*������Ԃ���̑J��*/
	EnemyStateType ChangeStateFromRefuge();
	/*�U����Ԃ���̑J��*/
	EnemyStateType ChangeStateFromAttack();
	/*�ǐՏ�Ԃ���̑J��*/
	EnemyStateType ChangeStateFromChase();

	void EnemyAttack();

	void Headbutt();

	void Rush();

	void NeedleFire();


};