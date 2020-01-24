#include "EnemyBase.h"
#include "../Player/TrpPlayer.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include "../Effect/Effects/DieEffect.h"
#include "../Effect/Effects/SleepEffect.h"
#include "../Collision/ShapeType/ShapeCircle.h"
#include "../Collision/ShapeType/ShapeRect.h"
#include "../Manager/CollisionManager.h"
#include "../Manager/ObjectManager.h"
#include<stdlib.h>


//�����܂�

EnemyBase::EnemyBase(float speed_, EnemyID enemy_id_,int max_wave_, float tex_size_)
	:ObjectBase(ObjectRavel::Ravel_Boss, Direction::LEFT, speed_, 0)
{
	m_enemy_id					= enemy_id_;
	m_state						= EnemyStateType::Walk;
	m_fatigue_gauge				= 0.f;
	m_sleep_gauge				= 0.f;
	m_is_delete					= false;
	m_pos.x						= M_INIT_POS_X;
	m_pos.y						= M_INIT_POS_Y - tex_size_ / 2.f;
	m_map_pos					= M_INIT_POS_X;
	m_draw_param.tu				= 1.f;
	m_draw_param.tv				= 1.f;
	m_draw_param.category_id	= TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id		= GameCategoryTextureList::GameEnemy_WalkLeft;
	m_draw_param.tex_size_x		= tex_size_;
	m_draw_param.tex_size_y		= tex_size_;
	m_anim_param.change_flame	= M_ANIM_FLAME;
	m_anim_param.split_all		= M_ANIM_TEX_ALL;
	m_anim_param.split_width	= M_ANIM_TEX_WIDTH;
	m_anim_param.split_height	= M_ANIM_TEX_HEIGHT;
	m_savetime_state			= 0;
	m_state_save_pos_x			= 0;
	m_p_pos_relation			= Direction::LEFT;
	m_now_ai					= EnemyAIType::AI1;
	m_now_ai_num				= -1;
	m_stop_state_transition		= false;
	m_hit_use_atk				= 0.f;
	m_auto_sleep_time			= M_AUTO_CHANGE_GAGE_FLAME;
	m_savetime_auto_slpgauge	= FlameTimer::GetNowFlame();
	m_stop_auto_sleep_time		= 0;
	m_savetime_end				= 0;
	m_fatigue_gage_stage		= EnemyGageStage::Zero;
	m_sleep_gage_stage			= EnemyGageStage::Zero;
	m_is_flying					= false;
	m_shot_adjust.x				= 0.f;
	m_shot_adjust.y				= 0.f;
	m_animation_stop			= false;
	m_now_wave					= 1;
	m_max_wave					= max_wave_;
	m_wave_state				= WaveState::None;
	m_player_center_pos			= 0.f;
	m_tex_space_front			= M_TEX_FRONT_SPACE;
	m_do_deadly_ai				= false;
	m_do_doraming				= false;
	m_savetime_wavechange = 0;

	AllInitEffect();

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

	AllDrawEffect();
	
}

void EnemyBase::Init()
{
	
}

void EnemyBase::Update()
{
	//�A�j���[�V����(�p���p���摜)�l�̍X�V
	if (m_animation_stop != true) {
		AnimationUpdate();
	}

	//State�̑J��
	//ChangeState();
	ObjectBase::Update();

	if (DataBank::Instance()->GetWavetype(WaveType::Wave1) != true)
	{
		//�f�o�b�O�p
		DebugKeyAction();

		//�f�[�^�o���N����̃f�[�^�̎擾
		DataGetUpdate();

		//�Q�[�W�̒i�K��ۑ��A��J�Q�[�W�ʂɂ���Ď����Q�[�W�ϓ�
		AutoChangeGageUpdate();

		//�e�̐���
		BulletControl();

		//�}�b�v�X�N���[���̈ʒu�v�Z
		CalcDrawPosition();

		//�f�[�^�o���N�ւ̒l�󂯓n��
		DataSetUpdate();

		// �G�t�F�N�g�A�b�v�f�[�g�֐��܂Ƃ�
		AllUpdateEffect();

		//���݂̏�Ԃɂ����铮��̍X�V
		//UpdateState();
		if (m_wave_state == WaveState::None) {
			//��ԓ���
			UpdateAIState();

		}
		else if (m_wave_state == WaveState::Change_Start) {
			//wave�J�ڒ��̓���(��ʒ[�ɑ����Ă���)
			WaveChangeState1();
		}
		else if (m_wave_state == WaveState::EnemyMoved) {
			WaveChangeState2();
		}
		else if (m_wave_state == WaveState::ItemGet) {
			//�Q�[���J�n
			if (FlameTimer::GetNowFlame(m_savetime_wavechange) > 120) {
				m_wave_state = WaveState::None;
			}
		}

		/*�ʒu�����̍X�V*/
		MoveLimitUpdate();

		// �����蔻��X�V�֐�
		CollisionParamUpdate();

	}
	if (DataBank::Instance()->GetWavetype(WaveType::Wave1) == true)
	{
		if (m_pos.x >= 960)
		{
			m_pos.x -= P_speed * 2;
		}
		else
		{
			DataBank::Instance()->SetWave(WaveType::Wave1, false);
		}
		if (m_pos.x <= 960)
		{
			m_pos.x += P_speed * 2;
		}
		else
		{
			DataBank::Instance()->SetWave(WaveType::Wave1, false);
		}

	}

	DataBank::Instance()->SetIsDebuff(m_is_debuff);
}

float EnemyBase::GetHitUseAtk(ObjectRavel hit_obj_)
{
	//1.f��Ԃ��ƃv���C���[�Ƀ_���[�W
	if (hit_obj_ == ObjectRavel::Ravel_Player) {

		if (m_state == EnemyStateType::Attack1 ||
			m_state == EnemyStateType::Attack2 ||
			m_state == EnemyStateType::Attack3 ||
			m_state == EnemyStateType::Attack4 ||
			m_state == EnemyStateType::Fly) {
			return 1.f;
		}
		else {
			return 0.f;
		}
	}

	return 0.0f;
}

Position EnemyBase::GetHandPos()
{
	Position pos;

	pos.x = m_map_pos + m_hand_pos.x;
	pos.y = m_pos.y + m_hand_pos.y;

	return pos;
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

	case EnemyStateType::Attack4:
		EnemyAttack4();
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
		EnemyMove();
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

	case EnemyStateType::Attack4:
		EnemyAttack4();
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

		CompleteChangeState();

	}

}

bool EnemyBase::AITransitionBase()
{
	//�������@��ʂ͒[�܂ł͂�����
	if (!m_is_animation_end)return false;

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

	float p_pos_x = DataBank::Instance()->GetPlayerMapPos();

	//�v���C���[��x���W���Q�b�g
	if (m_p_pos_relation == Direction::LEFT) {

		if (m_map_pos + m_draw_param.tex_size_x / 2.f <
			p_pos_x + G_PLAYER_SIZE / 2.f)
		{
			return true;
		}
	}
	else {

		if ((m_map_pos + m_draw_param.tex_size_x / 2.f) >
			p_pos_x + G_PLAYER_SIZE / 2.f)
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
			if ((p_pos_x + G_PLAYER_SIZE) >= (m_map_pos + m_tex_space_front + 120.f)) {
				return true;
			}
		}
	}
	else {
		//E=R,P=L
		if (m_p_pos_relation == Direction::RIGHT) {
			if (p_pos_x <= (m_map_pos + m_draw_param.tex_size_x - m_tex_space_front)) {
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
		&& m_is_animation_end)
	{
		return true;
	}

	return AITransitionBase();
}

bool EnemyBase::AITransitionFlameTime()
{
	if (FlameTimer::GetNowFlame(m_savetime_state) >= 
		m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_transition_num
		&& m_is_animation_end)
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

void EnemyBase::CompleteChangeState()
{
	//���̏�Ԃɍs�����߂̒l��ݒ�
	ChangeAIState();

	//�Q�[�W��Ԃɍ��킹�đ��x��ݒ�
	SetGageStateSpeed();

	//AI�ɍ��킹�Č����ύX
	ChangeAIDirection();

	//���C�E��J��ԑJ��
	if (CheckSleepGageMax()) {

		if (m_now_wave >= m_max_wave) {
			//�����Ԃ֑J�ځ��N���A
			ChangeState(EnemyStateType::Sleep);
		}
		else {
			//wave�J��
			++m_now_wave;
			
			DataBank::Instance()->SetWaveState(WaveState::Change_Start);

			m_wave_state = WaveState::Change_Start;

		}
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

void EnemyBase::AutoChangeGageUpdate()
{
	//�Q�[�W�̐i�s�x���i�[
	int fatigue_stage = GageStageCalc(m_fatigue_gauge, Fatigue_Gauge_Max, M_FATIGUE_GAGE_STAGE_NUM);
	int sleep_stage = GageStageCalc(m_sleep_gauge, Sleep_Gauge_Max, M_SLEEP_GAGE_STAGE_NUM);

	if (fatigue_stage >= 0 && fatigue_stage <= static_cast<int>(EnemyGageStage::Max)) {
		m_fatigue_gage_stage = static_cast<EnemyGageStage>(fatigue_stage);
	}
	if (fatigue_stage >= 0 && sleep_stage <= static_cast<int>(EnemyGageStage::Max)) {
		m_sleep_gage_stage = static_cast<EnemyGageStage>(sleep_stage);
	}

	
	float fatigue_up	= 0.f;
	float sleep_down	= 0.f;

	//�Q�[�W�����ϓ���~
	if (m_stop_auto_sleep_time > 0) {
		m_is_debuff = true;
		--m_stop_auto_sleep_time;
	}
	if (FlameTimer::GetNowFlame(m_savetime_auto_slpgauge) < M_AUTO_CHANGE_GAGE_FLAME) {
		return;
	}
	else {
		m_savetime_auto_slpgauge = FlameTimer::GetNowFlame();
	}

	//��J�Q�[�W�̒i�K
	switch (m_fatigue_gage_stage)
	{
	//0(�ŏ�)
	case EnemyGageStage::Zero:
		sleep_down = M_AUTO_SLEEP_UP_MAX_SPEED;
		break;

	//1�i�K�ځ@�`1/4
	case EnemyGageStage::Quarter:
		//���C�����F����
		sleep_down = M_AUTO_SLEEP_UP_HIGH_SPEED;
		break;

	//2�i�K�ځ@�`1/2
	case EnemyGageStage::Half_Down:
		//���C�����F����
		sleep_down = M_AUTO_SLEEP_UP_MEDIUM_SPEED;
		break;

	//3�i�K�ځ@�`3/4
	case EnemyGageStage::Half_Up:
		//���C�����F�ᑬ
		sleep_down = M_AUTO_SLEEP_UP_LOW_SPEED;
		fatigue_up = M_AUTO_FATIGUE_DOWN_LOW_SPEED;
		break;

	//4�i�K�ځ@�`�ő�
	case EnemyGageStage::Almost:
		//���C�����F��~�A��J�����F�ᑬ
		fatigue_up = M_AUTO_FATIGUE_DOWN_LOW_SPEED;
		break;

	//Max(�ő�)
	case EnemyGageStage::Max:
		//�G���S
		break;

	default:
		break;
	}

	//�Q�[�W�ϓ�
	UpFatigueGage(fatigue_up);

	if (m_stop_auto_sleep_time <= 0) {
		m_is_debuff = false;
		DownSleepGage(sleep_down);
	}
	

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

	//�S��ԋ��ʂ̏������֐�
	InitAllState();

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
		break;

	case EnemyStateType::Attack4:
		InitAttack4State();
		break;

	default:
		return;
	}

	//���݂̏�Ԃ��i�[
	m_savetime_state = FlameTimer::GetNowFlame();
	m_state_save_pos_x = m_map_pos;

	//�v���C���[���ǂ���̕����ɂ���̂����i�[
	if (m_map_pos + m_draw_param.tex_size_x / 2.f < DataBank::Instance()->GetPlayerMapPos() + G_PLAYER_SIZE / 2.f) {
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

	m_animation_stop = false;
	m_do_bullet = false;

}

void EnemyBase::InitWaitState()
{

	if (m_direction == Direction::LEFT) {
		//�g�p����摜�̕ύX(�ȉ�����)
		if (m_is_flying == true) {
			//��s��
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_SkyWaitLeft;
		}
		else if (m_fatigue_gage_stage >= EnemyGageStage::Half_Up) {
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
		else if (m_fatigue_gage_stage >= EnemyGageStage::Half_Up) {
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
	if (m_p_pos_relation == Direction::LEFT) {
		m_direction = Direction::RIGHT;
	}
	else {
		m_direction = Direction::LEFT;
	}

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
	m_savetime_end = FlameTimer::GetNowFlame();

	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_DownLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_DownRight;
	}
}

void EnemyBase::InitAttack4State()
{
	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_Attack4Left;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_Attack4Right;
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

void EnemyBase::WaveChangeState1()
{
	if (m_state != EnemyStateType::Walk) {
		m_direction = Direction::RIGHT;
		m_state = EnemyStateType::Walk;
		InitWalkState();
	}

	EnemyBase::EnemyMove();

	if (m_map_pos >= M_WAVE_CHANGE_MOVE_LIMIT) {

		m_map_pos = M_WAVE_CHANGE_MOVE_LIMIT;

		DataBank::Instance()->SetWaveState(WaveState::EnemyMoved);

		m_wave_state = WaveState::EnemyMoved;

		m_direction = Direction::LEFT;

		m_state = EnemyStateType::Wait;
		InitWaitState();
	}

}

void EnemyBase::WaveChangeState2()
{
	if (m_state != EnemyStateType::Walk) {
		m_sleep_gauge = 0.f;
		m_fatigue_gauge = 0.f;
		m_state = EnemyStateType::Walk;
		InitWalkState();
	}

	EnemyBase::EnemyMove();

	if (DataBank::Instance()->GetPlayerMapPos() + 1000.f > m_map_pos) {
		//�I��

		DataBank::Instance()->SetWaveState(WaveState::ItemGet);

		m_wave_state = WaveState::ItemGet;

		m_savetime_wavechange = FlameTimer::GetNowFlame();

		m_state = EnemyStateType::Wait;
		InitWaitState();
	}
}

//Csv�ǂݍ��݊֐�
void EnemyBase::LoadAIData(std::string file_name_)
{
	//�P�`�P�O�̊�{�z��
	for (int i = 0;i < static_cast<int>(EnemyAIType::EnemyAIType_Max);++i) {

		std::string f_name = file_name_ + std::to_string(i + 1) + ".csv";

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

	if (m_now_ai == EnemyAIType::DeadlyAi) {
		d_bank->SetDoEnemyDeadlyAi(true);
	}
	else {
		d_bank->SetDoEnemyDeadlyAi(false);
	}

}

void EnemyBase::DataGetUpdate()
{

	DataBank* d_bank = DataBank::Instance();

	m_player_center_pos = d_bank->GetPlayerMapPos() + G_PLAYER_SIZE / 2.f;

}

void EnemyBase::HitAction(ObjectRavel ravel_, float hit_use_atk_)
{

	if (m_do_doraming == true) {
		//�h���~���O���̏ꍇ�A������
		return;
	}

	//�����蔻��
	switch (ravel_)
	{
	//�v���C���[
	case ObjectRavel::Ravel_Player:
		break;

	//�v���C���[�e�@
	case ObjectRavel::Ravel_PlayerBullet:
		//���C����
		UpSleepGage(hit_use_atk_);
		m_stop_auto_sleep_time = M_STOP_AUTO_SLEEP_TIME_HITBULLET;
		break;

	//�v���C���[�e�A
	case ObjectRavel::Ravel_PlayerBullet2:
		//��J��
		DownFatigueGage(hit_use_atk_);
		m_stop_auto_sleep_time = M_STOP_AUTO_SLEEP_TIME_HITBULLET;
		break;

	//�v���C���[�e�B
	case ObjectRavel::Ravel_PlayerBullet3:
		UpFatigueGage(hit_use_atk_);
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
	if (m_fatigue_gage_stage > m_sleep_gage_stage && m_fatigue_gage_stage >= EnemyGageStage::Half_Up) {//�i�K3�̓Q�[�W�����ȏ�
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
}

void EnemyBase::EnemyDead()
{
	//�Q�[���I�[�o�[�t���O��DataBank�ɃZ�b�g
	if (FlameTimer::GetNowFlame(m_savetime_end) >= GAMEOVER_FLAME) {

		DataBank::Instance()->SetIsGameOver(true);

	}

	if (m_is_animation_end == true) {
		m_animation_stop = true;
		m_draw_param.tu = 4.f;
		m_draw_param.tv = 3.f;
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


Position EnemyBase::GetShotPos(Direction direction_)
{
	Position b_pos;

	//���ˈʒu����
	b_pos.y = m_pos.y + m_shot_adjust.y;

	if (direction_ == Direction::LEFT) {
		b_pos.x = m_map_pos + m_shot_adjust.x;
	}
	else {
		b_pos.x = m_map_pos - m_shot_adjust.x + m_draw_param.tex_size_x;
	}

	return b_pos;
}

void EnemyBase::CreateBullet(
	Direction direction_,
	float speed_x_, 
	float speed_y_, 
	bool is_rotate_, 
	int init_angle_,
	GameCategoryTextureList use_tex_,
	int tex_split_all_,
	int tex_split_w_,
	int tex_split_h,
	int use_tex_num_,
	float active_distance_,
	bool is_animation_stop_,
	float tex_size_
)
{

	//�e�̔��ˈʒu���擾
	Position b_pos = GetShotPos(static_cast<Direction>(m_direction));

	int draw_angle = 0;

	if (is_rotate_ == true) {

		float hypotenuse = pow((speed_x_ * speed_x_) + (speed_y_ * speed_y_), 0.5f);

		draw_angle = static_cast<int>(acosf(fabsf(speed_x_) / hypotenuse) * 180 / PI);

		draw_angle = init_angle_ - draw_angle;

		/*if (direction_ == Direction::LEFT) {
			draw_angle = init_angle_ - draw_angle;
		}
		else {
			draw_angle = init_angle_ + draw_angle;
		}*/

	}

	//�ʏ�e����
	bullet_list.push_back(
		new EnemyBullet(
			b_pos.x,
			b_pos.y,
			speed_x_,
			direction_,
			draw_angle,
			speed_y_,
			0.f,
			use_tex_,
			tex_split_w_,
			tex_split_h,
			tex_split_all_,
			use_tex_num_,
			active_distance_,
			is_animation_stop_,
			tex_size_
		)
	);

}

void EnemyBase::SetAIType()
{
	m_now_ai = ChangeAIType();
}

void EnemyBase::AllInitEffect()
{
	m_effect_list.push_back(new DieEffect(this));
	m_effect_list.push_back(new SleepEffect(this));
}

void EnemyBase::AllUpdateEffect()
{
	if (m_state == EnemyStateType::Dead) {
		m_effect_list.at(0)->WakeUp();
	}
	else {
		m_effect_list.at(0)->Sleep();
	}

	if (m_state == EnemyStateType::Sleep) {
		m_effect_list.at(1)->WakeUp();
	}
	else {
		m_effect_list.at(1)->Sleep();
	}

	m_effect_list.at(0)->Update();
	m_effect_list.at(1)->Update();
}

void EnemyBase::AllDrawEffect()
{
	m_effect_list.at(0)->Draw();
	m_effect_list.at(1)->Draw();
}

void EnemyBase::CollisionParamUpdate()
{

	for (const auto& i : m_shape_list)
	{
		i->Update(m_pos.x, m_pos.y, m_direction);
	}

	CollisionManager::GetInstance().AddEnemyColObject(this);

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

void EnemyBase::ChangeWave()
{

}

