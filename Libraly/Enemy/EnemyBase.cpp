#include "EnemyBase.h"
#include "../Player/TrpPlayer.h"
#include"../Engine/FileLoader.h"
#include"../Engine/Input.h"
#include<stdlib.h>

#define Num_of_TakeaBreak  100		//�x�e���Ƃ�i��J�x�́j���l
#define Refuge_Time	100				//������鎞��
#define Limit_of_BreakTime 100		//MAX�̋x�e����
#define Cure_of_SleepinessPoint 1	//���ԉ񕜂��閰�C�̒l
#define Cure_of_FatiguePoint 1		//���ԉ񕜂����J�̒l
#define Distance_of_Maintain 100	//�ێ�����K�؂ȋ���

#define Fatigue_Gauge_Max 100		//��J�Q�[�W���
#define Sleep_Gauge_Max	100			//�����Q�[�W���

#define Attack_Interval 100			//�U�����o

//�����܂�

EnemyBase::EnemyBase(float speed_, EnemyID enemy_id_)
	:ObjectBase(ObjectRavel::Ravel_Boss, Direction::LEFT, speed_)
{
	m_enemy_id			= enemy_id_;
	m_state				= EnemyStateType::Walk;
	m_attack_repertory	= 0;
	m_fatigue_gauge		= 0.f;
	m_sleep_gauge		= 0.f;
	m_time_of_break		= 0;
	m_is_break			= false;
	m_is_delete			= false;
	m_is_hit_judge		= false;
	m_pos.x				= M_INIT_POS_X;
	m_pos.y				= M_INIT_POS_Y;

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
	m_player_direction_relationship = Direction::LEFT;

	for (int i = 0;i < (int)EnemyAIType::EnemyAIType_Max;++i) {
		m_ai_list[i].clear();
	}

	m_now_ai				= EnemyAIType::AI1;
	m_now_ai_num			= 0;
	m_can_state_transition	= true;

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
}

void EnemyBase::Init()
{
	
}

void EnemyBase::Update()
{
	//State�̑J��
	//ChangeState();

	//�f�o�b�O�p
	DebugKeyAction();

	//���݂̏�Ԃɂ����铮��̍X�V
	UpdateState();

	//�A�j���[�V����(�p���p���摜)�l�̍X�V
	AnimationUpdate();

	//�e�̐���
	BulletControl();

}


EnemyStateType EnemyBase::GetEnemyState()	//�G�l�~�[�̏�Ԃ��擾
{
	return m_state;
}

//	�`�����܂Ł`

void EnemyBase::UpdateState()		//�G�l�~�[�̏�Ԃ̍X�V
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

		break;

	default:
		/*
			!!
		*/
		break;
	}

	
	//��Ԃ̕ύX
	if (m_state != next_state && m_can_state_transition) {
		//next_scene���p�̕ϐ��ɓn���A��ԑJ��
		ChangeState(next_state);
	}
	

}

void EnemyBase::UpdateAIState()
{
	bool can_change_ai_state = false;

	switch (m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_transition_term)
	{
		//��ʒ[�܂ňړ�
	case EnemyTransitionTerm::Straight:
		can_change_ai_state = TransitionStraight();
		break;

		//�v���C���[���z����
	case EnemyTransitionTerm::PassPlayer:
		can_change_ai_state = TransitionPassPlayer();
		break;

		//�v���C���[��O�ɂ����ꍇ
	case EnemyTransitionTerm::FrontPlayer:
		can_change_ai_state = TransitionFrontPlayer();
		break;

		//����
	case EnemyTransitionTerm::Distance:
		can_change_ai_state = TransitionDistance();
		break;

		//����
	case EnemyTransitionTerm::FlameTime:
		can_change_ai_state = TransitionFlameTime();
		break;

	default:
		break;
	}

	if (can_change_ai_state) {
		//���̏�Ԃ�
		ChangeAIState();
	}
}

bool EnemyBase::TransitionStraight()
{
	//�������@��ʂ͒[�܂ł͂�����
	if ((m_pos.x <= 0.f || (m_pos.x + m_draw_param.tex_size_x) > 1920.f)
		&& m_animation_end) 
	{
		return true;
	}

	return false;
}

bool EnemyBase::TransitionPassPlayer()
{
	//�v���C���[��x���W���Q�b�g

	return false;
}

bool EnemyBase::TransitionFrontPlayer()
{
	//�v���C���[��x���W���Q�b�g
	float p_pos_x;

	

	return false;
}

bool EnemyBase::TransitionDistance()
{
	if (fabsf(m_state_save_pos_x - m_pos.x) >=
		m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_transition_num
		&& m_animation_end)
	{
		return true;
	}

	return false;
}

bool EnemyBase::TransitionFlameTime()
{
	if (FlameTimer::GetNowFlame(m_state_saveflame) >= 
		m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_transition_num
		&& m_animation_end)
	{
		return true;
	}

	return false;
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

	//��ԑJ��
	ChangeState(m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_state);
	
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

	//���݂̏�Ԃ��i�[
	m_state_saveflame = FlameTimer::GetNowFlame();
	m_state_save_pos_x = m_pos.x;

	//�v���C���[���ǂ���̕����ɂ���̂����i�[
	m_player_direction_relationship = Direction::LEFT;

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

		FileLoadTool::w_vector<int*> file = FileLoad::GetFileDataInt(file_name_ + FileLoadTool::ItoC(i + 1) + ".csv");

		//vector�z��
		for (int j = 1;j < static_cast<int>(file[i].size());++j) {

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
		m_pos.x += m_speed;
	}
	else if (m_direction == Direction::LEFT) {
		m_pos.x -= m_speed;
	}

}

#if 0
void EnemyBase::EnemyChase_R()
{
	/*
		�G���������E�����։����ɂ���ꍇ�̒ǐ�
	*/

	m_pos.x + m_speed;

	m_enemy_to_player_state = EnemytoPlayerState::Separated;
}

void EnemyBase::EnemyChase_L()
{
	/*
		�G��������荶�����։����ɂ���ꍇ�̒ǐ�
	*/

	m_pos.x - m_speed;

	m_enemy_to_player_state = EnemytoPlayerState::Separated;
}

#endif

void EnemyBase::EnemyRefuge()		//��J��Ԃ̓���
{
	/*
		�s���`��Ԃ̃G�l�~�[����
	*/

	m_refuge_time--;

	if (m_refuge_time == 0)
	{
		m_is_break = true;
		m_refuge_time = Refuge_Time;
	}
	else
	{
		/*
			enemy�����鏈��
		*/

		//m_enemy_to_player_state = EnemytoPlayerState::Escape;

	}
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
			m_can_state_transition = !m_can_state_transition;
		}
		s_is_key = true;
	}
	else {
		s_is_key = false;
	}
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
	else
	{
		m_is_break = false;
	}
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

void EnemyBase::BackBeforeAttackState()
{
	EnemyStateType before_attack = GetEnemyState();

	m_state = EnemyStateType::Attack1;
	/*
		�e�G�l�~�[�U�����before_attack�̒��g��m_state�ɔ��f����
	*/
}

