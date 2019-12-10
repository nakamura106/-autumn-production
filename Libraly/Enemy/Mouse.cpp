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
	:EnemyBase(3.f,	EnemyID::Hedgehog)
{
	m_is_speed_up = false;
	m_do_needle = false;
	SetRectangle();

	LoadAIData(M_AIDataFileName);
	
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
	LoadTexture("Res/Tex/Enemy/Mouse/Boss1_FlyNeedle.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemy_Bullet_Needle);

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

	if (m_direction == Direction::LEFT) {
		m_world_pos.x -= m_speed * 2;
	}
	else {
		m_world_pos.x += m_speed * 2;
	}

}

void HedgeHog::EnemyAttack2()
{
	/*
		�Ƃ����ˏ���
		�Ƃ����˕����@�|���@�v���C���[�̍��W
		�ǔ��@�Ȃ�
		���ˁ@3way 2�񂭂炢�H
	*/
	if (GetAnimationTexNum() > 7 && !m_do_needle) {
		//���˂������ǂ����̃t���O��ON
		m_do_needle = true;

		//�e����
		CreateNeedle();

	}
}

void HedgeHog::EnemyAttack3()
{
	
}

EnemyStateType HedgeHog::ChangeStateFromWait()
{
	if (GetStateSaveFlame() > 120 && m_animation_end) {

		ChangeDirection();

		return EnemyStateType::Walk;
	}

	return EnemyStateType::Wait;
}

EnemyStateType HedgeHog::ChangeStateFromWalk()
{
	if (GetStateSaveFlame() > 60 && m_animation_end) {
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
	if (m_animation_end) {
		m_do_needle = false;
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

	return EnemyAIType::AI1;
}

void HedgeHog::InitAttack2State()
{
	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_NeedleAttackLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_NeedleAttackRight;
	}
}

void HedgeHog::CreateNeedle()
{
	Position b_pos;

	//���ˈʒu����
	b_pos.y = m_world_pos.y + M_NEEDLE_ADJUST_Y;

	if (m_direction == Direction::LEFT) {
		b_pos.x = m_world_pos.x + M_NEEDLE_ADJUST_X;
	}
	else {
		b_pos.x = m_world_pos.x - M_NEEDLE_ADJUST_X + m_draw_param.tex_size_x;
	}

	//Bullet(�n��)����
	CreateBullet(b_pos.x, b_pos.y, m_speed);
}

void HedgeHog::InitAllState()
{
	//�j�[�h�����Z�b�g
	m_do_needle = false;
}

