#include "Mouse.h"

//�萔�l�͉�����

#define Num_of_TakeaBreak  100		//�x�e���Ƃ�i��J�x�́j���l
#define Limit_of_BreakTime 100		//MAX�̋x�e����
#define Cure_of_SleepinessPoint 1	//���ԉ񕜂��閰�C�̒l
#define Cure_of_FatiguePoint 1		//���ԉ񕜂����J�̒l
#define Distance_of_Maintain 100	//�ێ�����K�؂ȋ���
#define Gauge_Variable 100			//�Q�[�W���ߗp
#define Attack_Interval	100			//�U���Ԋu

Hedgehog::Hedgehog()
{
	m_Enemy_Id = Enemy::Hedgehog;
	m_State = EnemyStateType::Warn;
	m_attack_repertory = AttackRepertoryofHedgeHog::AttackRepertoryMax;
	m_enemy_to_player_state = EnemytoPlayerState::EtoPStateTypeMax;
	m_fatigue_gauge = Gauge_Variable;
	m_sleep_gauge = Gauge_Variable;
	m_is_delete = false;

	m_time_of_break = 0;
	m_is_break = false;
	m_is_hit_judge = false;
	//	������
	m_pos.x = 500.0f;
	m_pos.y = 500.0f;
	m_speed = 10.0f;
}

Hedgehog::~Hedgehog()
{

}


void Hedgehog::ChangeState()
{

}

void Hedgehog::EnemyMove()
{

}

void Hedgehog::EnemyRefuge()
{

}

void Hedgehog::EnemyAttack()
{
	/*
		�G����v���C���[�ւ̏�Ԃɉ����čU�����ύX
	*/

	switch (m_enemy_to_player_state)
	{
	case EnemytoPlayerState::Separated:

		m_attack_repertory = AttackRepertoryofHedgeHog::Rush;
		Rush();
		break;

	case EnemytoPlayerState::Close:

		m_attack_repertory = AttackRepertoryofHedgeHog::HeadButt;
		Headbutt();
		break;

	case EnemytoPlayerState::Escape:

		m_attack_repertory = AttackRepertoryofHedgeHog::NeedleFire;
		NeedleFire();
		break;

	case EnemytoPlayerState::Pursue:

		m_attack_repertory = AttackRepertoryofHedgeHog::None;

		break;


	default:
		/*
			!!
		*/
		break;
	}

}

void Hedgehog::EnemyIdle()
{

}

void Hedgehog::EnemyBreak()
{

}

//	�n���l�Y�~Attack�̏����i���j

void Headbutt()
{
	/*
		���˂�����
		�v���C���[�����ɓ��˂�
		�������֑f�����ړ����Č��̍��W�܂Ŗ߂�
		���˂������@150
	*/

	


}

void Rush()
{
	/*
		�ːi����
		�������x�ő����Ă���
		�ړ����������߁@800
	*/



}

void NeedleFire()
{
	/*
		�Ƃ����ˏ���
		�Ƃ����˕����@�|���@�v���C���[�̍��W
		�ǔ��@�Ȃ�
		���ˁ@3way 2�񂭂炢�H
	*/



}

