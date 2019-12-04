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
	m_attack_repertory = AttackRepertoryofHedgeHog::None;
	m_enemy_to_player_state = EnemytoPlayerState::EtoPStateTypeMax;

	m_fatigue_gauge = NULL;
	m_sleep_gauge = NULL;
	m_time_of_break = 0;
	m_refuge_time = Refuge_Time;
	m_is_break = false;
	m_is_delete = true;
	m_is_hit_judge = false;
	m_is_speed_up = false;
	//m_speed = 5.0f;
}

HedgeHog::~HedgeHog()
{

}

void HedgeHog::Init()
{
	/*11/26 ��!!�������̃R�[�h*/
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Walk_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WalkLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Walk_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_WalkRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Tukare_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FatigueLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Tukare_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_FatigueRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Taiki_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_TaikiLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Taiki_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_TaikiRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Sleep_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SleepLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Sleep_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_SleepRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_DashAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DashAttackLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_DashAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DashAttackRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Down_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DownLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_Down_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_DownRight);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_TogeAttack_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_NeedleAttackLeft);
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_TogeAttack_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_NeedleAttackRight);
}

void HedgeHog::EnemyAttack()		//�G�l�~�[�U��
{
	/*
		�G����v���C���[�ւ̏�Ԃɉ����čU�����ύX
	*/

	switch (m_enemy_to_player_state)
	{
	case EnemytoPlayerState::Separated:
		Rush();
		m_attack_repertory = AttackRepertoryofHedgeHog::Rush;
		break;

	case EnemytoPlayerState::Close:
		Headbutt();
		m_attack_repertory = AttackRepertoryofHedgeHog::HeadButt;
		break;

	case EnemytoPlayerState::Escape:
		NeedleFire();
		m_attack_repertory = AttackRepertoryofHedgeHog::NeedleFire;
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

EnemyStateType HedgeHog::ChangeStateFromWait()
{
	if (FlameTimer::GetNowFlame(m_state_saveflame) > 120 && m_animation_end) {

		ChangeDirection();

		return EnemyStateType::Walk;
	}

	return EnemyStateType::Wait;
}

EnemyStateType HedgeHog::ChangeStateFromWalk()
{
	if (FlameTimer::GetNowFlame(m_state_saveflame) > 120 && m_animation_end) {
		return EnemyStateType::Attack;
	}

	return EnemyStateType::Walk;
}

EnemyStateType HedgeHog::ChangeStateFromRefuge()
{
	return EnemyStateType::Refuge;
}

EnemyStateType HedgeHog::ChangeStateFromAttack()
{
	if (m_animation_end) {
		return EnemyStateType::Wait;
	}

	return EnemyStateType::Attack;
}

EnemyStateType HedgeHog::ChangeStateFromChase()
{
	return EnemyStateType::Chase;
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

