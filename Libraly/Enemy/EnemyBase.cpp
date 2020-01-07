#include "EnemyBase.h"
#include "../Player/TrpPlayer.h"
#include"../Engine/FileLoader.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include<stdlib.h>

#define Num_of_TakeaBreak  100		//�x�e���Ƃ�i��J�x�́j���l
#define Refuge_Time	100				//������鎞��
#define Limit_of_BreakTime 100		//MAX�̋x�e����
#define Cure_of_SleepinessPoint 0.5f	//���ԉ񕜂��閰�C�̒l
#define Cure_of_FatiguePoint 1		//���ԉ񕜂����J�̒l
#define Distance_of_Maintain 100	//�ێ�����K�؂ȋ���

#define Fatigue_Gauge_Max 100		//��J�Q�[�W���
#define Sleep_Gauge_Max	75			//�����Q�[�W���

#define Attack_Interval 100			//�U�����o

//�����܂�

EnemyBase::EnemyBase(float speed_, EnemyID enemy_id_)
	:ObjectBase(ObjectRavel::Ravel_Boss, Direction::LEFT, speed_)
{
	m_enemy_id					= enemy_id_;
	m_state						= EnemyStateType::Walk;
	m_fatigue_gauge				= 0.f;
	m_sleep_gauge				= 0.f;
	m_is_delete					= false;
	m_pos.x						= M_INIT_POS_X;
	m_pos.y						= M_INIT_POS_Y;
	m_map_pos					= M_INIT_POS_X;
	m_draw_param.tu				= 1.f;
	m_draw_param.tv				= 1.f;
	m_draw_param.category_id	= TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id		= GameCategoryTextureList::GameEnemy_WalkLeft;
	m_draw_param.tex_size_x		= M_ENEMY_SYZE;
	m_draw_param.tex_size_y		= M_ENEMY_SYZE;
	m_anim_param.change_flame	= M_ANIM_FLAME;
	m_anim_param.split_all		= M_ANIM_TEX_ALL;
	m_anim_param.split_width	= M_ANIM_TEX_WIDTH;
	m_anim_param.split_height	= M_ANIM_TEX_HEIGHT;
	m_savetime_state			= 0;
	m_state_save_pos_x			= 0;
	m_p_pos_relation			= Direction::LEFT;
	m_now_ai					= EnemyAIType::AI1;
	m_now_ai_num				= 0;
	m_stop_state_transition		= false;
	m_hit_use_atk				= 0.f;
	m_auto_sleep_time			= M_CURE_SLEEP_TIME_DEFAULT;
	m_savetime_auto_slpgauge	= FlameTimer::GetNowFlame();
	m_stop_auto_sleep_time		= 0;
	m_savetime_end				= 0;
	m_fatigue_gage_stage		= 0;
	m_sleep_gage_stage			= 0;
	m_is_flying					= false;
	m_shot_adjust.x				= 0.f;
	m_shot_adjust.y				= 0.f;

	DataBank::Instance()->SetIsGameClear(false);

}

EnemyBase::~EnemyBase()
{
	//bullet���
	for (auto& i : bullet_list) {
		delete i;
		i = nullptr;
	}
	std::vector<EnemyBullet*>().swap(bullet_list);

	//AI���X�g��delete
	for (int i = 0;i < (int)EnemyAIType::EnemyAIType_Max;++i) {

		for (int j = 0;j < static_cast<int>(m_ai_list[i].size());++j) {

			if (m_ai_list[i][j] != nullptr)delete m_ai_list[i][j];

		}
	}

}

void EnemyBase::Draw()
{
	//�G�l�~�[�̕`��
	ObjectBase::Draw();

	//�e�̕`��
	for (const auto& i : bullet_list) {

		if (i != nullptr) {
			i->Draw();
		}

	}

	//�f�o�b�O�`��
	/*
	DrawFont(
		m_pos.x + m_draw_param.tex_size_x / 2,
		m_pos.y + m_draw_param.tex_size_y / 2,
		std::to_string(m_fatigue_gauge).c_str(),
		FontSize::Large,
		FontColor::Red
	);
	*/
}

void EnemyBase::Init()
{
	
}

void EnemyBase::Update()
{
	//State�̑J��
	//ChangeState();
	ObjectBase::Update();

	//�f�o�b�O�p
	DebugKeyAction();

	//�Q�[�W�̒i�K��ۑ��A��J�Q�[�W�ʂɂ���Ď����Q�[�W�ϓ�
	AutoChangeGageUpdate();

	//���݂̏�Ԃɂ����铮��̍X�V
	//UpdateState();
	UpdateAIState();

	/*�ʒu�����̍X�V*/
	MoveLimitUpdate();

	//�A�j���[�V����(�p���p���摜)�l�̍X�V
	AnimationUpdate();

	//�e�̐���
	BulletControl();

	//�}�b�v�X�N���[���̈ʒu�v�Z
	CalcDrawPosition();

	//�f�[�^�o���N�ւ̒l�󂯓n��
	DataSetUpdate();

}

//�G�l�~�[�̏�Ԃ̍X�V
void EnemyBase::UpdateState()
{
	//���̏�Ԃ������ϐ�
	EnemyStateType next_state = m_state;

	switch (m_state)
	{
	//�ҋ@���
	case EnemyStateType::Wait:
		EnemyWait();
		next_state = ChangeStateFromWait();
		break;

	//�ړ����
	case EnemyStateType::Walk:
		EnemyMove();
		next_state = ChangeStateFromWalk();
		break;

	//�U��1���
	case EnemyStateType::Attack1:
		EnemyAttack1();
		next_state = ChangeStateFromAttack1();
		break;

	//�U��2���
	case EnemyStateType::Attack2:
		EnemyAttack2();
		break;

	//�U��3���
	case EnemyStateType::Attack3:
		EnemyAttack3();
		break;

	//�������(�Q�[�W�����ȉ��̏ꍇ�����鏈��)
	case EnemyStateType::Refuge:
		EnemyRefuge();
		next_state = ChangeStateFromRefuge();
		break;

	//�ǐՏ��
	case EnemyStateType::Chase:
		next_state = ChangeStateFromChase();
		break;

	//�������(���C�xMAX)
	case EnemyStateType::Sleep:
		return;

	//��s���
	case EnemyStateType::Fly:
		EnemyFly();
		break;

	default:
		/*
			!!
		*/
		break;
	}

	
	//��Ԃ̕ύX
	if (m_state != next_state && m_stop_state_transition) {
		//next_scene���p�̕ϐ��ɓn���A��ԑJ��
		ChangeState(next_state);
	}
	

}

void EnemyBase::UpdateAIState()
{
	switch (m_state)
	{
		//�ҋ@���
	case EnemyStateType::Wait:
		EnemyWait();
		break;

		//�ړ����
	case EnemyStateType::Walk:
		EnemyMove();
		break;

		//�U��1���
	case EnemyStateType::Attack1:
		EnemyAttack1();
		break;

		//�U��2���
	case EnemyStateType::Attack2:
		EnemyAttack2();
		break;

		//�U��3���
	case EnemyStateType::Attack3:
		EnemyAttack3();
		break;

		//�������(�Q�[�W�����ȉ��̏ꍇ�����鏈��)
	case EnemyStateType::Refuge:
		EnemyRefuge();
		break;

		//�ǐՏ��
	case EnemyStateType::Chase:
		EnemyMove();
		break;

		//�������(���C�xMAX)
	case EnemyStateType::Sleep:
		EnemySleep();
		return;

		//���S���(��J�xMAX)
	case EnemyStateType::Dead:
		EnemyDead();
		return;

	case EnemyStateType::Fly:
		EnemyFly();
		break;

	default:
		/*
			!!
		*/
		break;
	}

	//AI��ԑJ��
	AITransitionUpdate();

}

void EnemyBase::AITransitionUpdate()
{
	//��s��Ԃ̏ꍇ�A��ԑJ�ږ���
	if (m_state == EnemyStateType::Fly)return;

	bool can_change_ai_state = false;

	switch (m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_transition_term)
	{
		//��ʒ[�܂ňړ�
	case EnemyTransitionTerm::Straight:
		can_change_ai_state = AITransitionStraight();
		break;

		//�v���C���[���z����
	case EnemyTransitionTerm::PassPlayer:
		can_change_ai_state = AITransitionPassPlayer();
		break;

		//�v���C���[��O�ɂ����ꍇ
	case EnemyTransitionTerm::FrontPlayer:
		can_change_ai_state = AITransitionFrontPlayer();
		break;

		//����
	case EnemyTransitionTerm::Distance:
		can_change_ai_state = AITransitionDistance();
		break;

		//����
	case EnemyTransitionTerm::FlameTime:
		can_change_ai_state = AITransitionFlameTime();
		break;

	default:
		break;
	}


	//��ԑJ�ځEAI�ύX���s��
	if (can_change_ai_state && !m_stop_state_transition) {

		//���̏�Ԃɍs�����߂̒l��ݒ�
		ChangeAIState();

		//�Q�[�W��Ԃɍ��킹�đ��x��ݒ�
		SetGageStateSpeed();

		//AI�ɍ��킹�Č����ύX
		ChangeAIDirection();

		if (CheckSleepGageMax()) {
			//���C�Q�[�W���ő�̏ꍇ�A�����Ԃ֑J��
			ChangeState(EnemyStateType::Sleep);
		}
		else if (CheckFatigueGageMax()) {
			//��J�Q�[�W���ő�̏ꍇ�A���S��Ԃ֑J��
			ChangeState(EnemyStateType::Dead);
		}
		else {
			//�l�ɉ����ď�ԑJ��
			ChangeState(m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_state);
		}
	}

}

bool EnemyBase::AITransitionBase()
{
	//�������@��ʂ͒[�܂ł͂�����
	if (!m_animation_end)return false;

	if (m_direction == Direction::LEFT) {
		return IsMoveLimitLeft();
	}
	else {
		return IsMoveLimitRight();
	}
	
	return false;
}

bool EnemyBase::AITransitionStraight()
{
	return AITransitionBase();
}

bool EnemyBase::AITransitionPassPlayer()
{
	//�v���C���[��x���W���Q�b�g
	if (m_p_pos_relation == Direction::LEFT) {

		if (m_map_pos + m_draw_param.tex_size_x / 2.f <
			DataBank::Instance()->GetPlayerMapPos())
		{
			return true;
		}
	}
	else {

		if ((m_map_pos + m_draw_param.tex_size_x / 2.f) >
			DataBank::Instance()->GetPlayerMapPos())
		{
			return true;
		}
	}

	return AITransitionBase();
}

bool EnemyBase::AITransitionFrontPlayer()
{

	float p_pos_x = DataBank::Instance()->GetPlayerMapPos();

	//�v���C���[��x���W���Q�b�g
	
	if (m_direction == Direction::LEFT) {
		//E=L,P=L
		if (m_p_pos_relation == Direction::LEFT) {
			if (p_pos_x + M_PLAYER_SIZE_X >= m_map_pos) {
				return true;
			}
		}
	}
	else {
		//E=R,P=L
		if (m_p_pos_relation == Direction::RIGHT) {
			if (p_pos_x <= (m_map_pos + m_draw_param.tex_size_x)) {
				return true;
			}
		}
	}

	//��ԑJ�ڏ����l�͈ړ������ł����肷�邽�߂ɑ���(�l0�̏ꍇ�͔��薳��)
	if (m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_transition_num != 0) {

		return AITransitionDistance();

	}

	return false;
}

bool EnemyBase::AITransitionDistance()
{
	if (fabsf(m_state_save_pos_x - m_map_pos) >=
		m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_transition_num
		&& m_animation_end)
	{
		return true;
	}

	return AITransitionBase();
}

bool EnemyBase::AITransitionFlameTime()
{
	if (FlameTimer::GetNowFlame(m_savetime_state) >= 
		m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_transition_num
		&& m_animation_end)
	{
		return true;
	}

	return AITransitionBase();
}

void EnemyBase::ChangeAIDirection()
{
	switch (m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_direction)
	{
	case EnemyDirection::Right:
		m_direction = Direction::RIGHT;
		break;

	case EnemyDirection::Left:
		m_direction = Direction::LEFT;
		break;

	case EnemyDirection::Reverse:
		m_direction = !m_direction;
		break;

	default:
		break;
	}

	if (m_direction == Direction::LEFT) {
		if (IsMoveLimitLeft()) {
			m_direction = Direction::RIGHT;
		}
	}
	else {
		if (IsMoveLimitRight()) {
			m_direction = Direction::LEFT;
		}
	}

}

void EnemyBase::SetGageStateSpeed()
{

	switch (CheckGaugeState())
	{
	case GageState::Normal_State:
		//�G�̃Q�[�W�ʂɂ���ăX�s�[�h���ω�
		m_speed = (float)m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_speed_default;
		break;

	case GageState::Fatigue_State:
		//�G�̃Q�[�W�ʂɂ���ăX�s�[�h���ω�
		m_speed = (float)m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_speed_fatigue;
		break;

	case GageState::Sleep_State:
		//�G�̃Q�[�W�ʂɂ���ăX�s�[�h���ω�
		m_speed = (float)m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_speed_sleep;
		break;

	default:
		m_speed = (float)m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_speed_default;
		break;
	}

}

void EnemyBase::AutoChangeGageUpdate()
{
	//�Q�[�W�̐i�s�x���i�[
	m_fatigue_gage_stage	= GageStageCalc(m_fatigue_gauge, Fatigue_Gauge_Max, M_FATIGUE_GAGE_STAGE_NUM);
	m_sleep_gage_stage		= GageStageCalc(m_sleep_gauge, Sleep_Gauge_Max, M_SLEEP_GAGE_STAGE_NUM);

	float fatigue_up	= 0.f;
	float sleep_down	= 0.f;

	//�Q�[�W�����ϓ���~
	if (m_stop_auto_sleep_time > 0) {
		--m_stop_auto_sleep_time;
		return;
	}
	if (FlameTimer::GetNowFlame(m_savetime_auto_slpgauge) < M_CURE_SLEEP_TIME_DEFAULT) {
		return;
	}
	else {
		m_savetime_auto_slpgauge = FlameTimer::GetNowFlame();
	}

	//��J�Q�[�W�̒i�K
	switch (m_fatigue_gage_stage)
	{
	//0(�ŏ�)
	case 0:
		sleep_down = M_AUTO_SLEEP_UP_MAX_SPEED;
		break;

	//1�i�K�ځ@�`1/4
	case 1:
		//���C�����F����
		sleep_down = M_AUTO_SLEEP_UP_HIGH_SPEED;
		break;

	//2�i�K�ځ@�`1/2
	case 2:
		//���C�����F����
		sleep_down = M_AUTO_SLEEP_UP_MEDIUM_SPEED;
		break;

	//3�i�K�ځ@�`3/4
	case 3:
		//���C�����F�ᑬ
		sleep_down = M_AUTO_SLEEP_UP_LOW_SPEED;
		break;

	//4�i�K�ځ@�`�ő�
	case 4:
		//���C�����F��~�A��J�����F�ᑬ
		fatigue_up = M_AUTO_FATIGUE_DOWN_LOW_SPEED;
		break;

	//Max(�ő�)
	case 5:
		//�G���S
		break;

	default:
		break;
	}

	//�Q�[�W�ϓ�
	m_fatigue_gauge += fatigue_up;

	m_sleep_gauge -= sleep_down;

	//�Q�[�W�̃R���g���[��
	GaugeLimitControl();

}

int EnemyBase::GageStageCalc(float now_gage_, float max_gage_, int gage_stage_num_)
{
	//�Q�[�W���ő�̏ꍇ�A�i�K��+1�̒l��Ԃ�
	if (now_gage_ >= max_gage_) {
		++gage_stage_num_;
		return gage_stage_num_;
	}

	//�Q�[�W��0(�ŏ�)�̏ꍇ�A0��Ԃ�
	if (now_gage_ == 0.f) {
		return 0;
	}

	//�Q�[�W�̒i�K���ɉ��������݂̐i�s�i�K��Ԃ�
	return static_cast<int>(now_gage_ / (max_gage_ / static_cast<float>(gage_stage_num_))) + 1;
}



void EnemyBase::ChangeAIState()		//�G�l�~�[���s���������
{
	if (static_cast<int>(m_now_ai) >= static_cast<int>(EnemyAIType::EnemyAIType_Max)) {
		//�G���[:�A�N�Z�X����ꏊ�����݂��Ȃ�
		return;
	}

	//�g�p��AI�����̏�Ԃɐi�s
	++m_now_ai_num;
	
	if (m_now_ai_num >= static_cast<int>(m_ai_list[static_cast<int>(m_now_ai)].size())) {

		//ai�̕ύX
		//�����ŁAAI��������֐����Ăяo��
		EnemyAIType next_ai = ChangeAIType();

		//�Ԃ��Ă����l�������l�̏ꍇ�A�uAI1�v�ɂ���
		if (next_ai >= EnemyAIType::EnemyAIType_Max) {
			next_ai = EnemyAIType::AI1;
		}

		//AI�ύX
		m_now_ai = next_ai;
		m_now_ai_num = 0;

	}
	
}

void EnemyBase::ChangeState(EnemyStateType next_state_)
{
	//��ԕύX
	m_state = next_state_;

	switch (next_state_)
	{
	case EnemyStateType::Wait:
		InitWaitState();
		break;

	case EnemyStateType::Walk:
		InitWalkState();
		break;

	case EnemyStateType::Attack1:
		InitAttack1State();
		//InitAttackRepertory();
		break;

	case EnemyStateType::Attack2:
		InitAttack2State();
		break;

	case EnemyStateType::Attack3:
		InitAttack3State();
		break;

	case EnemyStateType::Refuge:
		InitRefugeState();
		break;

	case EnemyStateType::Chase:
		InitChaseState();
		break;

	case EnemyStateType::Sleep:
		InitSleepState();
		break;

	case EnemyStateType::Dead:
		InitDeadState();
		break;

	case EnemyStateType::Fly:
		InitFlyState();

	default:
		return;
	}

	//�S��ԋ��ʂ̏������֐�
	InitAllState();

	//���݂̏�Ԃ��i�[
	m_savetime_state = FlameTimer::GetNowFlame();
	m_state_save_pos_x = m_map_pos;

	//�v���C���[���ǂ���̕����ɂ���̂����i�[
	if (m_map_pos < DataBank::Instance()->GetPlayerMapPos()) {
		m_p_pos_relation = Direction::RIGHT;
	}
	else {
		m_p_pos_relation = Direction::LEFT;
	}

}
 


EnemyStateType EnemyBase::ChangeStateFromWait()
{
	return EnemyStateType::Wait;
}

EnemyStateType EnemyBase::ChangeStateFromWalk()
{
	return EnemyStateType::Walk;
}

EnemyStateType EnemyBase::ChangeStateFromRefuge() 
{
	return EnemyStateType::Refuge;
}

EnemyStateType EnemyBase::ChangeStateFromAttack1()
{
	return EnemyStateType::Attack1;
}

EnemyStateType EnemyBase::ChangeStateFromChase()
{
	return EnemyStateType::Chase;
}



void EnemyBase::InitAllState()
{
	m_draw_param.tu = 1.f;
	m_draw_param.tv = 1.f;
}

void EnemyBase::InitWaitState()
{

	if (m_direction == Direction::LEFT) {
		//�g�p����摜�̕ύX(�ȉ�����)
		if (m_is_flying == true) {
			//��s��
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_SkyWaitLeft;
		}
		else if (m_fatigue_gage_stage > M_FATIGUE_GAGE_STAGE_NUM / 2) {
			//��J���
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_FatigueLeft;
		}
		else {
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_WaitLeft;
		}
	}
	else {
		if (m_is_flying == true) {
			//��s��
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_SkyWaitRight;
		}
		else if (m_fatigue_gage_stage > M_FATIGUE_GAGE_STAGE_NUM / 2) {
			//��J���
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_FatigueRight;
		}
		else {
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_WaitRight;
		}
	}

}

void EnemyBase::InitWalkState()
{
	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_WalkLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_WalkRight;
	}

}

void EnemyBase::InitRefugeState()
{
	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_WalkLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_WalkRight;
	}

}

void EnemyBase::InitAttack1State()
{
	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_Attack1Left;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_Attack1Right;
	}
}

void EnemyBase::InitAttack2State()
{

	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_Attack2Left;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_Attack2Right;
	}
}

void EnemyBase::InitAttack3State()
{
	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_Attack3Left;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_Attack3Right;
	}
}

void EnemyBase::InitChaseState()
{
	//�������v���C���[�̑��ɂ���
	m_direction = m_p_pos_relation;

	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_WalkLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_WalkRight;
	}

}

void EnemyBase::InitSleepState()
{
	m_savetime_end = FlameTimer::GetNowFlame();

	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_SleepLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_SleepRight;
	}

}

void EnemyBase::InitFlyState()
{
	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_SkyWaitLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_SkyWaitRight;
	}

}

void EnemyBase::InitDeadState()
{
	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_DownLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_DownRight;
	}
}

void EnemyBase::ChangeDirection()
{
	if (m_direction == Direction::LEFT) {
		m_direction = Direction::RIGHT;
	}
	else {
		m_direction = Direction::LEFT;
	}
}

//Csv�ǂݍ��݊֐�
void EnemyBase::LoadAIData(std::string file_name_)
{
	//�P�`�P�O�̊�{�z��
	for (int i = 0;i < static_cast<int>(EnemyAIType::EnemyAIType_Max);++i) {

		std::string f_name = file_name_ + FileLoadTool::ItoC(i + 1) + ".csv";

		FileLoadTool::w_vector<int*> file = FileLoad::GetFileDataInt(f_name);

		//vector�z��
		for (int j = 1;j < static_cast<int>(file.size());++j) {

			//vector�g��
			m_ai_list[i].push_back(new EnemyAIParam());


			//��Ԃ��i�[
			if (*file[j][static_cast<int>(EnemyAIArrayNum::State)] < static_cast<int>(EnemyStateType::EnemyStateType_Max)) {
				m_ai_list[i][j - 1]->e_state = (EnemyStateType)* file[j][static_cast<int>(EnemyAIArrayNum::State)];
			}
			else {
				m_ai_list[i][j - 1]->e_state = EnemyStateType::Wait;
			}

			//��Ԍp���������i�[
			if (*file[j][static_cast<int>(EnemyAIArrayNum::Transition_Term)] < static_cast<int>(EnemyTransitionTerm::EnemyTransitionTerm_Max)) {
				m_ai_list[i][j - 1]->e_transition_term = (EnemyTransitionTerm)* file[j][static_cast<int>(EnemyAIArrayNum::Transition_Term)];
			}
			else {
				m_ai_list[i][j - 1]->e_transition_term = EnemyTransitionTerm::FlameTime;
			}

			//�s�����x�l���i�[
			m_ai_list[i][j - 1]->e_speed_default = *file[j][static_cast<int>(EnemyAIArrayNum::Speed_Default)];
			m_ai_list[i][j - 1]->e_speed_sleep = *file[j][static_cast<int>(EnemyAIArrayNum::Speed_Sleep)];
			m_ai_list[i][j - 1]->e_speed_fatigue = *file[j][static_cast<int>(EnemyAIArrayNum::Speed_Tired)];

			//��Ԍp�������Ŏg�p����l���i�[
			m_ai_list[i][j - 1]->e_transition_num = *file[j][static_cast<int>(EnemyAIArrayNum::Transition_Num)];

			//���������i�[
			if (*file[j][static_cast<int>(EnemyAIArrayNum::Enemy_Direction)] < static_cast<int>(EnemyDirection::EnemyDirection_Max)) {
				m_ai_list[i][j - 1]->e_direction = static_cast<EnemyDirection>(*file[j][static_cast<int>(EnemyAIArrayNum::Enemy_Direction)]);
			}
			else {
				m_ai_list[i][j - 1]->e_direction = EnemyDirection::Same;
			}
		}
	}
}



//�G�l�~�[�ړ�
void EnemyBase::EnemyMove()			
{
	/*
		�ʏ��Ԃ̃G�l�~�[�ړ��i�K�؂ȋ����܂ŋ������l�߂�j
	*/

	if (m_direction == Direction::RIGHT) {
		m_map_pos += m_speed;
	}
	else if (m_direction == Direction::LEFT) {
		m_map_pos -= m_speed;
	}

}

void EnemyBase::BulletControl()
{
	for (int i = 0;i < static_cast<int>(bullet_list.size());++i) {
		//�e�̍X�V
		bullet_list[i]->Update();

		//�e��is_delete��true�̏ꍇ�A�e����
		if (bullet_list[i]->GetIsDelete()) {
			//���������
			delete bullet_list[i];

			//�e������
			bullet_list.erase(bullet_list.begin() + i);

		}
	}
}

void EnemyBase::DebugKeyAction()
{
	static bool s_is_key = false;

	if (GetKey(E_KEY)) {
		if (!s_is_key) {
			//�҂���ԂɑJ��
			ChangeState(EnemyStateType::Wait);
			m_stop_state_transition = !m_stop_state_transition;
		}
		s_is_key = true;
	}
	else {
		s_is_key = false;
	}
}

void EnemyBase::DataSetUpdate()
{
	//�f�[�^�o���N�ɒl������
	DataBank* d_bank = DataBank::Instance();

	d_bank->SetSleepGauge(m_sleep_gauge);
	d_bank->SetFatigueGauge(m_fatigue_gauge);

}

void EnemyBase::HitAction(ObjectRavel ravel_, float hit_use_atk_)
{
	//�����蔻��
	switch (ravel_)
	{
	//�v���C���[
	case ObjectRavel::Ravel_Player:
		break;

	//�v���C���[�e�@
	case ObjectRavel::Ravel_PlayerBullet:
		//���C����
		UpSleepGage(hit_use_atk_ / 2.f);
		m_stop_auto_sleep_time = M_STOP_AUTO_SLEEP_TIME_HITBULLET;
		break;

	//�v���C���[�e�A
	case ObjectRavel::Ravel_PlayerBullet2:
		//��J��
		DownFatigueGage(hit_use_atk_ / 2.f);
		m_stop_auto_sleep_time = M_STOP_AUTO_SLEEP_TIME_HITBULLET;
		break;

	//�v���C���[�e�B
	case ObjectRavel::Ravel_PlayerBullet3:
		UpFatigueGage(hit_use_atk_ / 2.f);
		m_stop_auto_sleep_time = M_STOP_AUTO_SLEEP_TIME_HITBULLET;
		break;

	//�v���C���[�e�C
	case ObjectRavel::Ravel_PlayerBullet4:
		m_stop_auto_sleep_time = static_cast<int>(hit_use_atk_);
		break;

	default:
		break;
	}
}

bool EnemyBase::IsMoveLimitLeft()
{
	//�ʒu������
	if (m_map_pos <= 0.f) {
		return true;
	}

	return false;
}

bool EnemyBase::IsMoveLimitRight()
{
	//�ʒu�����E
	if ((m_map_pos + m_draw_param.tex_size_x) > M_MOVE_LIMIT_X) {
		return true;
	}
	return false;
}

void EnemyBase::MoveLimitUpdate()
{
	if (IsMoveLimitLeft()) {
		m_map_pos = 0.f;
	}
	if (IsMoveLimitRight()) {
		m_map_pos = M_MOVE_LIMIT_X - m_draw_param.tex_size_x;
	}
}

bool EnemyBase::CheckSleepGageMax()
{
	return (m_sleep_gauge >= Sleep_Gauge_Max);
}

bool EnemyBase::CheckFatigueGageMax()
{
	return (m_fatigue_gauge >= Fatigue_Gauge_Max);
}


GageState EnemyBase::CheckGaugeState()
{
	//��J���
	if (m_fatigue_gage_stage > m_sleep_gage_stage) {
		return GageState::Fatigue_State;
	}
	
	//���C(�C���C��)���
	if (m_sleep_gage_stage > m_fatigue_gage_stage) {
		return GageState::Sleep_State;
	}

	return GageState::Normal_State;

}

void EnemyBase::GaugeLimitControl()
{
	if (m_fatigue_gauge < 0.f) {
		m_fatigue_gauge = 0.f;
	}
	else {
		if (m_fatigue_gauge > Fatigue_Gauge_Max) {
			m_fatigue_gauge = Fatigue_Gauge_Max;
		}
	}

	if (m_sleep_gauge < 0.f) {
		m_sleep_gauge = 0.f;
	}
	else {
		if (m_sleep_gauge > Sleep_Gauge_Max) {
			m_sleep_gauge = Sleep_Gauge_Max;
		}
	}
}


void EnemyBase::EnemySleep()
{
	//�Q�[���N���A�t���O��DataBank�ɃZ�b�g
	if (FlameTimer::GetNowFlame(m_savetime_end) >= GAMECLEAR_FLAME) {

		DataBank::Instance()->SetIsGameClear(true);

	}
}

void EnemyBase::EnemyFly()
{

	if (m_is_flying == true) {
		//�n��ɍ~��Ă���
		m_pos.y += m_speed;

		//�~��Ă���
		if (m_pos.y >= M_INIT_POS_Y) {

			m_pos.y = M_INIT_POS_Y;

			m_is_flying = false;

			ChangeState(EnemyStateType::Wait);

		}
	}
	else {
		//���ɔ��ł���
		m_pos.y -= m_speed;

		//���܂Ŕ��
		if (m_pos.y <= M_SKY_HEIGHT) {

			m_pos.y = M_SKY_HEIGHT;

			m_is_flying = true;

			ChangeState(EnemyStateType::Wait);

		}
	}

}

void EnemyBase::EnemyDead()
{
	//�Q�[���I�[�o�[�t���O��DataBank�ɃZ�b�g
	if (FlameTimer::GetNowFlame(m_savetime_end) >= GAMEOVER_FLAME) {

		DataBank::Instance()->SetIsGameOver(true);

	}
}

void EnemyBase::DownSleepGage(float down_num_)
{
	m_sleep_gauge -= down_num_;

	//�ŏ��l�Ŏ~�߂�
	if (m_sleep_gauge <= 0.f) {
		m_sleep_gauge = 0.f;
	}
}

void EnemyBase::DownFatigueGage(float down_num_)
{
	m_fatigue_gauge -= down_num_;

	//�ŏ��l�Ŏ~�߂�
	if (m_fatigue_gauge <= 0.f) {
		m_fatigue_gauge = 0.f;
	}
}

int EnemyBase::GetStateSaveFlame()
{
	return FlameTimer::GetNowFlame(m_savetime_state);
}


Position EnemyBase::GetShotPos()
{
	Position b_pos;

	//���ˈʒu����
	b_pos.y = m_pos.y + m_shot_adjust.y;

	if (m_direction == Direction::LEFT) {
		b_pos.x = m_map_pos + m_shot_adjust.x;
	}
	else {
		b_pos.x = m_map_pos - m_shot_adjust.x + m_draw_param.tex_size_x;
	}

	return b_pos;
}

void EnemyBase::CreateBullet()
{

	//�e�̔��ˈʒu���擾
	Position b_pos = GetShotPos();

	//�ʏ�e����
	bullet_list.push_back(
		new EnemyBullet(
			b_pos.x,
			b_pos.y,
			m_speed,
			(Direction)m_direction
		)
	);

}

void EnemyBase::UpSleepGage(float up_num_)
{
	m_sleep_gauge += up_num_;

	//�ő�l�Ŏ~�߂�
	if (m_sleep_gauge >= Sleep_Gauge_Max) {

		m_sleep_gauge = Sleep_Gauge_Max;

		//1���Ԃ̎����񕜒�~
		m_stop_auto_sleep_time = 3600;

	}

}

void EnemyBase::UpFatigueGage(float up_num_)
{
	m_fatigue_gauge += up_num_;

	//�ő�l�Ŏ~�߂�
	if (m_fatigue_gauge >= Fatigue_Gauge_Max) {

		m_fatigue_gauge = Fatigue_Gauge_Max;

	}
}

