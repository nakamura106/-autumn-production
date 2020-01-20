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
	:EnemyBase(2.f, EnemyID::Hedgehog, 1, 512.f)
{

	LoadAIData(M_AIDataFileName);
	CompleteChangeState();

	m_is_speed_up = false;
	m_do_bullet = false;
	SetRectangle();
	m_shot_adjust.x = M_NEEDLE_ADJUST_X;
	m_shot_adjust.y = M_NEEDLE_ADJUST_Y;

}

HedgeHog::~HedgeHog()
{

}

void HedgeHog::Init()
{
	
}


void HedgeHog::SetRectangle()
{
	m_rect_param.shift_x = 250.f;//105.0f;
	m_rect_param.shift_y = 440.0f;
	m_rect_param.width = 829.0f;
	m_rect_param.height = 561.0f;
}

void HedgeHog::EnemyAttack1()		//�G�l�~�[�U��
{
	/*
		�ːi����
		�������㓯�����x�Ō���
	*/

	if (GetAnimationTexNum() > M_ATTACK1_ANIM_TEX_NUM) {
		m_speed /= M_DASHATTACK_SPEED_CHANGE_NUM;
	}
	else {
		m_speed *= M_DASHATTACK_SPEED_CHANGE_NUM;
	}

	EnemyBase::EnemyMove();

}

void HedgeHog::EnemyAttack2()
{
	/*
		�Ƃ����ˏ���
		�Ƃ����˕����@�|���@�v���C���[�̍��W
		�ǔ��@�Ȃ�
		���ˁ@3way 2�񂭂炢�H
	*/
	if (GetAnimationTexNum() > M_ATTACK2_ANIM_TEX_NUM && !m_do_bullet) {
		//���˂������ǂ����̃t���O��ON
		m_do_bullet = true;

		//�e����
		CreateBullet(static_cast<Direction>(m_direction), m_speed);

	}
}

void HedgeHog::EnemyAttack3()
{
	int num = GetAnimationTexNum();

	if (num == M_ATTACK3_ANIM_TEX_NUM) {
		EnemyMove();
	}
}

EnemyStateType HedgeHog::ChangeStateFromWait()
{
	//�g�p���Ă��Ȃ��֐��ł���A�����I�ɏ������邽�߃}�W�b�N�i���o�[�̂܂�
	if (GetStateSaveFlame() > 120 && m_is_animation_end) {

		ChangeDirection();

		return EnemyStateType::Walk;
	}

	return EnemyStateType::Wait;
}

EnemyStateType HedgeHog::ChangeStateFromWalk()
{
	//�g�p���Ă��Ȃ��֐��ł���A�����I�ɏ������邽�߃}�W�b�N�i���o�[�̂܂�
	if (GetStateSaveFlame() > 60 && m_is_animation_end) {
		return EnemyStateType::Attack1;
	}

	return EnemyStateType::Walk;
}

EnemyStateType HedgeHog::ChangeStateFromRefuge()
{
	return EnemyStateType::Refuge;
}

EnemyStateType HedgeHog::ChangeStateFromAttack1()
{
	if (m_is_animation_end) {
		m_do_bullet = false;
		return EnemyStateType::Wait;
	}

	return EnemyStateType::Attack1;
}

EnemyStateType HedgeHog::ChangeStateFromChase()
{
	return EnemyStateType::Chase;
}

EnemyAIType HedgeHog::ChangeAIType()
{
	//Enemy�̈ʒu������A�v���C���[�Ƃ̊֌W�ɂ����
	//���Ɏg�p����AI���ω�����

	if (GetNowAI() == EnemyAIType::AI1) {
		return EnemyAIType::AI2;
	}
	else if (GetNowAI() == EnemyAIType::AI2) {
		return EnemyAIType::AI3;
	}
	else {
		return EnemyAIType::AI1;
	}

	return EnemyAIType::AI1;
}


void HedgeHog::InitAllState()
{
	EnemyBase::InitAllState();
}

