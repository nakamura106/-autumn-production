#pragma once
#include "EnemyBase.h"




class HedgeHog :public EnemyBase
{
public:
	HedgeHog();
	~HedgeHog();
	
	void Init();

	void SetRectangle()override;

private:
	

	//�n�����ˈʒu�����p
	//note:Adjust�́u�����v�Ƃ����Ӗ�
	const float M_NEEDLE_ADJUST_X = 180.f;
	const float M_NEEDLE_ADJUST_Y = 630.f;

	const float M_DASHATTACK_SPEED_CHANGE_NUM = 1.02f;

	//�U��������̃^�C�~���O�萔
	const int	M_ATTACK1_ANIM_TEX_NUM = 9;
	const int	M_ATTACK2_ANIM_TEX_NUM = 7;
	const int	M_ATTACK3_ANIM_TEX_NUM = 5;

	
	const std::string M_AIDataFileName = "Res/Csv/Mouse/Enemy_AI";
	bool m_is_speed_up;		//�������邩	
	//AttackRepertoryHedgeHog m_attack_repertory;

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
	//void InitAttackRepertory();

	/*EnemyBase�ŌĂяo���U������*/
	void EnemyAttack1();
	void EnemyAttack2();
	void EnemyAttack3();
	
	/*�n������*/
	void CreateNeedle();

	void InitAllState();

	//bool m_is_speed_up;		//�������邩
	bool m_do_needle;		//�n�����˂��s�������ǂ���
};