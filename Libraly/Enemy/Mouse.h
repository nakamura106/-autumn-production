#pragma once
#include "EnemyBase.h"




class HedgeHog :public EnemyBase
{
public:
	HedgeHog();
	~HedgeHog();
	
	void Init();
	//void Update();

	void SetRectangle()override;
	

private:
	//�n���l�Y�~�̍U�����p�[�g���[
	enum class AttackRepertoryHedgeHog
	{
		Rush,		//�ːi
		HeadButt,	//���˂�
		NeedleFire,	//�g�Q����
		AttackRepertoryMax
	};

	//�n�����ˈʒu�����p
	//note:Adjust�́u�����v�Ƃ����Ӗ�
	const float M_NEEDLE_ADJUST_X = 180.f;
	const float M_NEEDLE_ADJUST_Y = 630.f;
	
	std::string M_AIDataFileName = "Res/Csv/Mouse/EnemyAI";
	bool m_is_speed_up;		//�������邩	
	AttackRepertoryHedgeHog m_attack_repertory;

	/*�ҋ@��Ԃ���̑J��*/
	EnemyStateType ChangeStateFromWait();
	/*�ړ���Ԃ���̑J��*/
	EnemyStateType ChangeStateFromWalk();
	/*������Ԃ���̑J��*/
	EnemyStateType ChangeStateFromRefuge();
	/*�U����Ԃ���̑J��*/
	EnemyStateType ChangeStateFromAttack1();
	/*�ǐՏ�Ԃ���̑J��*/
	EnemyStateType ChangeStateFromChase();

	/*AI�ύX�֐�*/
	EnemyAIType ChangeAIType();

	/*�U�����p�[�g���[�̏�����*/
	void InitAttackRepertory();

	/*EnemyBase�ŌĂяo���U������*/
	void EnemyAttack1();
	void EnemyAttack2();
	void EnemyAttack3();
	
	/*�n������*/
	void CreateNeedle();

	//bool m_is_speed_up;		//�������邩
	bool m_do_needle;		//�n�����˂��s�������ǂ���
};