#include "EnemyBase.h"
#include "../Player/TrpPlayer.h"

#define Num_of_TakeaBreak  100		//�x�e���Ƃ�i��J�x�́j���l
#define Limit_of_BreakTime 100		//MAX�̋x�e����
#define Cure_of_SleepinessPoint 1	//���ԉ񕜂��閰�C�̒l
#define Cure_of_FatiguePoint 1		//���ԉ񕜂����J�̒l
#define Distance_of_Maintain 100	//�ێ�����K�؂ȋ���

//���ϐ��i�萔�j�p�ӂł����������

const int player_pos_x = 100;
const int player_pos_y = 100;

//�����܂�

TrpPlayer trpplayer;

EnemyBase::EnemyBase()
{
	m_enemy_id = EnemyID::BossTypeMax;
	m_state = EnemyStateType::EnemyStateTypeMax;
	m_attack_repertory = EnemyAttackRepertory::VariableEnumrate_Type;
	m_enemy_to_player_state = EnemytoPlayerState::EtoPStateTypeMax;

	m_fatigue_gauge = 0.f;
	m_sleep_gauge = 0.f;
	m_time_of_break = 0;
	m_is_break = false;
	m_is_delete = false;
	m_is_hit_judge = false;

	m_anim_timer = 0;

	//	������
	m_pos.x = 500.0f;
	m_pos.y = 0.0f;
	

	//�`����i�[
	m_draw_param.tu = 1;
	m_draw_param.tv = 1;
	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id = GameCategoryTextureList::GameBoss_WalkTex;
	
}

EnemyBase::~EnemyBase()
{
	
}

void EnemyBase::Init()
{
	/*11/26 ��!!�������̃R�[�h*/
	LoadTexture("Res/Tex/Boss1_Walk_Left.png", m_draw_param.category_id, m_draw_param.texture_id);
}

void EnemyBase::Update()
{
	AnimationUpdate();
}

void EnemyBase::Draw()
{
	//ObjectBase::Draw();

	DrawUVTexture(
		m_pos.x, 
		m_pos.y, 
		M_ENEMY_SYZE, 
		M_ENEMY_SYZE, 
		GetTexture(m_draw_param.category_id, m_draw_param.texture_id), 
		m_draw_param.tu / M_ANIM_TEX_WIDTH, 
		m_draw_param.tv / M_ANIM_TEX_HEIGHT
	);

}

void EnemyBase::AnimationUpdate() {

	++m_anim_timer;

	if (m_anim_timer >= M_ANIM_FLAME) {//�摜��ύX����

		m_anim_timer = 0;

		//���������ڂ����Z
		++m_draw_param.tu;

		//���������ڂ��摜�̕������ȏ�̏ꍇ
		if (m_draw_param.tu > M_ANIM_TEX_WIDTH) {

			m_draw_param.tu = 1;

			//�c�������ڂ����Z
			++m_draw_param.tv;
		}

		//�c�������ڂ��摜�̕������ȏ�̏ꍇ
		if (m_draw_param.tv > M_ANIM_TEX_HEIGHT) {

			m_draw_param.tv = 1;

		}

		//tu��tv����v�Z�������݉����ڂ̃A�j���[�V���������������𒴂��Ă����ꍇ�A
		//tu��tv�����Z�b�g
		if (((m_draw_param.tv - 1) * M_ANIM_TEX_WIDTH + m_draw_param.tu) > M_ANIM_TEX_ALL) {

			m_draw_param.tu = m_draw_param.tv = 1;

		}

	}

}


EnemyStateType EnemyBase::GetEnemyState()	//�G�l�~�[�̏�Ԃ��擾
{
	return m_state;
}

//	�`�����܂Ł`

void EnemyBase::UpdateState()		//�G�l�~�[�̏�Ԃ̍X�V	//�K�v�H�H
{
	switch (m_state)
	{
	case EnemyStateType::Idle:

		EnemyIdle();

		break;

	case EnemyStateType::Break:

		EnemyBreak();

		break;

	case EnemyStateType::Warn:

		EnemyMove();

		break;

	case EnemyStateType::Attack:

		EnemyAttack();

		break;

	case EnemyStateType::Refuge:

		EnemyRefuge();

		break;

	default:
		/*
			!!
		*/
		break;
	}
}

void EnemyBase::ChangeState()		//�G�l�~�[���s���������
{
	/*
		�G�l�~�[�̏�Ԃ̕ύX
	*/

	if (m_fatigue_gauge <= Num_of_TakeaBreak)
	{
		if (m_time_of_break < Limit_of_BreakTime)
		{
			m_is_break = true;
			m_state = EnemyStateType::Break;
			m_time_of_break++;
		}
		else if (m_is_break == true)
		{
			m_state = EnemyStateType::Refuge;
			m_time_of_break--;
			if (m_time_of_break == 0)
			{
				m_is_break = false;
			}
		}
	}

	/*
		�v���C���[�̈ʒu�����擾���āA�K�؂ȋ�����ۂB
	*/
}

void EnemyBase::EnemyMove()			//�G�l�~�[�ړ�
{
	/*
		�ʏ��Ԃ̃G�l�~�[�ړ��i�K�؂ȋ����܂ŋ������l�߂�j
	*/

	if (m_pos.x < player_pos_x + Distance_of_Maintain || m_pos.x < player_pos_x - Distance_of_Maintain)
	{
		m_pos.x;		//��������
	}

}

void EnemyBase::EnemyRefuge()		//��J��Ԃ̓���
{
	/*
		�s���`��Ԃ̃G�l�~�[����
	*/



}

void EnemyBase::EnemyAttack()		//�G�l�~�[�U��
{
	/*
		�G����v���C���[�ւ̏�Ԃɉ����čU�����ύX
	*/

	switch (m_enemy_to_player_state)
	{
	case EnemytoPlayerState::Separated:

		m_attack_repertory = EnemyAttackRepertory::VariableEnumrate_Type;

		break;

	case EnemytoPlayerState::Close:

		m_attack_repertory = EnemyAttackRepertory::VariableEnumrate_Type;

		break;

	case EnemytoPlayerState::Escape:

		m_attack_repertory = EnemyAttackRepertory::VariableEnumrate_Type;

		break;

	case EnemytoPlayerState::Pursue:

		m_attack_repertory = EnemyAttackRepertory::VariableEnumrate_Type;

		break;


	default:
		/*
			!!
		*/
		break;
	}

}

void EnemyBase::EnemyIdle()			//�G�l�~�[�ҋ@
{
	/*
		�G�l�~�[�̑ҋ@�i���̏�őҋ@�A�j���[�V�����j
	*/



}

void EnemyBase::EnemyBreak()		//�G�l�~�[�x�e
{
	/*
		�G�l�~�[�̔�J�ҋ@�i���̏�Ŕ�J�ҋ@�A�j���[�V�����j
	*/



}

void EnemyBase::CureSleepiness()
{
	m_sleep_gauge -= Cure_of_SleepinessPoint;
}

void EnemyBase::CureFatigue()
{
	m_fatigue_gauge -= Cure_of_FatiguePoint;
}

void EnemyBase::DamageSleepness(int damage_sleep_)
{
	m_sleep_gauge += damage_sleep_;
}

void EnemyBase::DamageFatigue(int damage_fatigue_)
{
	m_fatigue_gauge += damage_fatigue_;
}


