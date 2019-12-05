#pragma once
#include "EnemyBase.h"




class HedgeHog :public EnemyBase
{
public:
	HedgeHog();
	~HedgeHog();
	
	void Init();
	//void Update();
	

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

	/*�U�����p�[�g���[�̏�����*/
	void InitAttackRepertory();

	/*EnemyBase�ŌĂяo���U������*/
	void EnemyAttack();

	/*�n���l�Y�~�e�U���̏���*/
	void Headbutt();
	void Rush();
	void ShotNeedle();
	
	/*�n������*/
	void CreateNeedle();

	bool m_is_speed_up;		//�������邩
	bool m_do_needle;		//�n�����˂��s�������ǂ���
};