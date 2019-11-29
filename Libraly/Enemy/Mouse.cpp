#include "Mouse.h"
#include "../Player/TrpPlayer.h"

//�萔�l�͉�����

#define Num_of_TakeaBreak  100		//�x�e���Ƃ�i��J�x�́j���l
#define Refuge_Time	100				//������鎞��
#define Limit_of_BreakTime 100		//MAX�̋x�e����
#define Cure_of_SleepinessPoint 1	//���ԉ񕜂��閰�C�̒l
#define Cure_of_FatiguePoint 1		//���ԉ񕜂����J�̒l
#define Distance_of_Maintain 100	//�ێ�����K�؂ȋ���

#define Fatigue_Gauge_Max 100		//��J�Q�[�W���
#define Sleep_Gauge_Max	100			//�����Q�[�W���

#define Attack_Interval 100			//�U�����o
#define HedgeHog_Speed 10			//�ǂ�Ŏ��̔@��

TrpPlayer* trpplayer;

HedgeHog::HedgeHog()
{
	m_enemy_id = EnemyID::BossTypeMax;
	m_state = EnemyStateType::EnemyStateTypeMax;
	m_attack_repertory = EnemyAttackRepertory::None;
	m_enemy_to_player_state = EnemytoPlayerState::EtoPStateTypeMax;

	m_fatigue_gauge = NULL;
	m_sleep_gauge = NULL;
	m_time_of_break = 0;
	m_refuge_time = Refuge_Time;
	m_is_break = false;
	m_is_delete = true;
	m_is_hit_judge = false;
	m_is_speed_up = false;
	//	������
	m_pos.x = 500.0f;
	m_pos.y = 500.0f;
	m_speed = 10.0f;
}

HedgeHog::~HedgeHog()
{

}

void HedgeHog::Init()
{

}

void HedgeHog::Create()
{

}

void HedgeHog::Update()
{

}

void HedgeHog::Draw()
{

}

void HedgeHog::EnemyAttack()		//�G�l�~�[�U��
{
	/*
		�G����v���C���[�ւ̏�Ԃɉ����čU�����ύX
	*/

	switch (m_enemy_to_player_state)
	{
	case EnemytoPlayerState::Separated:

		m_attack_repertory = EnemyAttackRepertory::Rush;

		break;

	case EnemytoPlayerState::Close:

		m_attack_repertory = EnemyAttackRepertory::HeadButt;

		break;

	case EnemytoPlayerState::Escape:

		m_attack_repertory = EnemyAttackRepertory::NeedleFire;

		break;

	case EnemytoPlayerState::Pursue:

		m_attack_repertory = EnemyAttackRepertory::None;

		break;


	default:
		/*
			!!
		*/
		break;
	}

}


//	�n���l�Y�~Attack�̏����i���j

void HedgeHog::Headbutt()
{
	/*
		���˂�����
		�v���C���[�����ɓ��˂�
		�������֑f�����ړ����Č��̍��W�܂Ŗ߂�
		���˂������@150
	*/

	//	�A�j���[�V�����ύX

}

void HedgeHog::Rush()
{
	/*
		�ːi����
		�������㓯�����x�Ō���
	*/

	//	�A�j���[�V�����ύX

}

void HedgeHog::NeedleFire()
{
	/*
		�Ƃ����ˏ���
		�Ƃ����˕����@�|���@�v���C���[�̍��W
		�ǔ��@�Ȃ�
		���ˁ@3way 2�񂭂炢�H
	*/

	//	�A�j���[�V�����ύX����H

}

