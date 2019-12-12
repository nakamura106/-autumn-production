#include "EnemyBase.h"
#include "../Player/TrpPlayer.h"
#include"../Engine/FileLoader.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include<stdlib.h>

#define Num_of_TakeaBreak  100		//�x�e���Ƃ�i��J�x�́j���l
#define Refuge_Time	100				//������鎞��
#define Limit_of_BreakTime 100		//MAX�̋x�e����
#define Cure_of_SleepinessPoint 0.1f	//���ԉ񕜂��閰�C�̒l
#define Cure_of_FatiguePoint 1		//���ԉ񕜂����J�̒l
#define Distance_of_Maintain 100	//�ێ�����K�؂ȋ���

#define Fatigue_Gauge_Max 100		//��J�Q�[�W���
#define Sleep_Gauge_Max	100			//�����Q�[�W���

#define Attack_Interval 100			//�U�����o

//�����܂�

EnemyBase::EnemyBase(float speed_, EnemyID enemy_id_)
	:ObjectBase(ObjectRavel::Ravel_Boss, Direction::LEFT, speed_)
{
	m_state				= EnemyStateType::Walk;
	m_fatigue_gauge		= 0.f;
	m_sleep_gauge		= 0.f;
	m_is_delete			= false;
	m_pos.x				= M_INIT_POS_X;
	m_pos.y				= M_INIT_POS_Y;
	m_map_pos = M_INIT_POS_X;

	//�`����i�[
	m_draw_param.tu				= 1;
	m_draw_param.tv				= 1;
	m_draw_param.category_id	= TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id		= GameCategoryTextureList::GameEnemy_WalkLeft;
	m_draw_param.tex_size_x		= M_ENEMY_SYZE;
	m_draw_param.tex_size_y		= M_ENEMY_SYZE;

	//�A�j���[�V�������i�[
	m_anim_param.change_flame	= M_ANIM_FLAME;
	m_anim_param.split_all		= M_ANIM_TEX_ALL;
	m_anim_param.split_width	= M_ANIM_TEX_WIDTH;
	m_anim_param.split_height	= M_ANIM_TEX_HEIGHT;

	//saveflame(�t���[�����v���p�ϐ�)
	m_state_saveflame = 0;
	m_state_save_pos_x = 0;
	m_player_pos_relationship = Direction::LEFT;

	for (int i = 0;i < (int)EnemyAIType::EnemyAIType_Max;++i) {
		m_ai_list[i].clear();
	}

	m_now_ai				= EnemyAIType::AI1;
	m_now_ai_num			= 0;
	m_stop_state_transition	= false;
	m_is_pos_end			= false;
	m_hit_use_atk = 0.f;
	m_auto_sleep_time = M_CURE_SLEEP_TIME_DEFAULT;
	m_auto_sleep_saveflame = FlameTimer::GetNowFlame();
	m_stop_auto_sleep_time = 0;

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
	DrawFont(
		m_pos.x + m_draw_param.tex_size_x / 2.f,
		m_pos.y + m_draw_param.tex_size_y / 2.f,
		std::to_string(m_sleep_gauge).c_str(),
		FontSize::Large,
		FontColor::Red
	);
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

	//���݂̏�Ԃɂ����铮��̍X�V
	//UpdateState();
	UpdateAIState();

	//�A�j���[�V����(�p���p���摜)�l�̍X�V
	AnimationUpdate();

	//�e�̐���
	BulletControl();

	//�Q�[�W������
	AutoCureSleepGage();

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
		return;

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

		//�G�̃Q�[�W�ʂɂ���ăX�s�[�h���ω�
		m_speed = m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_speed_default;

		//AI�ɍ��킹�Č����ύX
		ChangeAIDirection();

		if (!CheckSleepState()) {
			//�l�ɉ����ď�ԑJ��
			ChangeState(m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_state);
		}
		else {
			ChangeState(EnemyStateType::Sleep);
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
	if (m_player_pos_relationship == Direction::LEFT) {

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
		if (m_player_pos_relationship == Direction::LEFT) {
			if (p_pos_x + 256.f >= m_map_pos) {
				return true;
			}
		}
	}
	else {
		//E=R,P=L
		if (m_player_pos_relationship == Direction::RIGHT) {
			if (p_pos_x <= (m_map_pos + m_draw_param.tex_size_x)) {
				return true;
			}
		}
	}

	return AITransitionBase();
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
	if (FlameTimer::GetNowFlame(m_state_saveflame) >= 
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

	default:
		return;
	}

	//�S��ԋ��ʂ̏������֐�
	InitAllState();

	//���݂̏�Ԃ��i�[
	m_state_saveflame = FlameTimer::GetNowFlame();
	m_state_save_pos_x = m_map_pos;

	//�v���C���[���ǂ���̕����ɂ���̂����i�[
	if (m_map_pos < DataBank::Instance()->GetPlayerMapPos()) {
		m_player_pos_relationship = Direction::RIGHT;
	}
	else {
		m_player_pos_relationship = Direction::LEFT;
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



void EnemyBase::InitWaitState()
{
	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_TaikiLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_TaikiRight;
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
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_DashAttackLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_DashAttackRight;
	}
}

void EnemyBase::InitAttack2State()
{

	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_NeedleAttackLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_NeedleAttackRight;
	}
}

void EnemyBase::InitAttack3State()
{
	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_DashAttackLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_DashAttackRight;
	}
}

void EnemyBase::InitChaseState()
{
	//�������v���C���[�̑��ɂ���
	m_direction = m_player_pos_relationship;

	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_WalkLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_WalkRight;
	}

}

void EnemyBase::InitSleepState()
{
	if (m_direction == Direction::LEFT) {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_SleepLeft;
	}
	else {
		m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_SleepRight;
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
			if (*file[j][static_cast<int>(EnemyAIArrayNum::State)] < static_cast<int>(EnemyStateType::EnemyStateTypeMax)) {
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
			m_ai_list[i][j - 1]->e_speed_tired = *file[j][static_cast<int>(EnemyAIArrayNum::Speed_Tired)];

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



void EnemyBase::EnemyMove()			//�G�l�~�[�ړ�
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

void EnemyBase::EnemyRefuge()		//��J��Ԃ̓���
{
	/*
		�s���`��Ԃ̃G�l�~�[����
	*/

}

void EnemyBase::EnemyAttack1()		//�G�l�~�[�U��
{
}

void EnemyBase::EnemyAttack2()
{
}

void EnemyBase::EnemyAttack3()
{
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
	switch (ravel_)
	{
	case ObjectRavel::Ravel_Player:
		break;
	case ObjectRavel::Ravel_PlayerBullet:
		//���C����
		DamageSleepness(5.f);
		break;

	case ObjectRavel::Ravel_PlayerBullet2:
		//��J��
		CureFatigue(5.f);
		break;

	case ObjectRavel::Ravel_PlayerBullet3:
		DamageFatigue(5.f);
		break;

	case ObjectRavel::Ravel_PlayerBullet4:
		m_stop_auto_sleep_time = M_STOP_AUTO_SLEEP_TIME_DEFAULT;
		break;

	default:
		break;
	}
}

void EnemyBase::AutoCureSleepGage()
{
	if (m_stop_auto_sleep_time > 0) {
		--m_stop_auto_sleep_time;
		return;
	}

	if (FlameTimer::GetNowFlame(m_auto_sleep_saveflame)>=m_auto_sleep_time) {

		//������
		CureSleepiness(Cure_of_SleepinessPoint);

		//�t���[�������L�[�v
		m_auto_sleep_saveflame = FlameTimer::GetNowFlame();

	}
}

bool EnemyBase::IsMoveLimitLeft()
{
	if (m_map_pos <= 0.f) {
		return true;
	}
	return false;
}

bool EnemyBase::IsMoveLimitRight()
{
	if ((m_map_pos + m_draw_param.tex_size_x) > 2500.f) {
		return true;
	}
	return false;
}

bool EnemyBase::CheckSleepState()
{
	return m_sleep_gauge >= Sleep_Gauge_Max;
}

void EnemyBase::EnemyWait()			//�G�l�~�[�ҋ@
{
	/*
		�G�l�~�[�̑ҋ@�i���̏�őҋ@�A�j���[�V�����j
	*/



}

void EnemyBase::EnemyChase()
{



}

void EnemyBase::EnemyRest()		//�G�l�~�[�x�e
{
	/*
		�G�l�~�[�̔�J�ҋ@�i���̏�Ŕ�J�ҋ@�A�j���[�V�����j
	*/

	int cure_fatigue = (int)(Fatigue_Gauge_Max - m_fatigue_gauge);

	if (cure_fatigue > 0)
	{
		m_fatigue_gauge -= Cure_of_FatiguePoint * 5;	//���������ʏ�񕜂̌ܔ{���炢�H
		cure_fatigue -= Cure_of_FatiguePoint * 5;
	}
}

void EnemyBase::CureSleepiness(float cure_sleep_)
{
	m_sleep_gauge -= cure_sleep_;

	if (m_sleep_gauge <= 0.f) {
		m_sleep_gauge = 0.f;
	}
}

void EnemyBase::CureFatigue(float cure_fatigue_)
{
	m_fatigue_gauge -= cure_fatigue_;

	if (m_fatigue_gauge <= 0.f) {
		m_fatigue_gauge = 0.f;
	}
}

int EnemyBase::GetStateSaveFlame()
{
	return FlameTimer::GetNowFlame(m_state_saveflame);
}

void EnemyBase::CreateBullet(float pos_x_,float pos_y_,float move_speed_)
{
	bullet_list.push_back(new EnemyBullet(pos_x_, pos_y_, move_speed_, (Direction)m_direction));
}

void EnemyBase::DamageSleepness(int damage_sleep_)
{
	m_sleep_gauge += damage_sleep_;

	if (m_sleep_gauge >= Sleep_Gauge_Max) {
		m_sleep_gauge = Sleep_Gauge_Max;

		//1���Ԃ̎����񕜒�~
		m_stop_auto_sleep_time = 3600;

	}

}

void EnemyBase::DamageFatigue(int damage_fatigue_)
{
	m_fatigue_gauge += damage_fatigue_;

	if (m_fatigue_gauge >= Fatigue_Gauge_Max) {
		m_fatigue_gauge = Fatigue_Gauge_Max;
	}

}

