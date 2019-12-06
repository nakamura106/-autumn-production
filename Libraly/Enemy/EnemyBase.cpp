#include "EnemyBase.h"
#include "../Player/TrpPlayer.h"
#include"../Engine/FileLoader.h"

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

EnemyBase::EnemyBase()
{
	m_enemy_id				= EnemyID::BossTypeMax;
	m_state					= EnemyStateType::Walk;
	m_attack_repertory		= EnemyAttackRepertory::VariableEnumrate_Type;
	m_enemy_to_player_state = EnemytoPlayerState::EtoPStateTypeMax;

	m_fatigue_gauge = 0.f;
	m_sleep_gauge	= 0.f;
	m_time_of_break = 0;
	m_is_break		= false;
	m_is_delete		= false;
	m_is_hit_judge	= false;
	m_speed			= 3.f;
	m_direction		= Direction::LEFT;

//	TrpPlayer* trpplayer;

	//	������
	m_pos.x = M_INIT_POS_X;
	m_pos.y = M_INIT_POS_Y;
	

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

	for (int i = 0;i < G_ENEMY_AILIST_MAX;++i) {
		m_ai_list[i].clear();
	}
	
}

EnemyBase::~EnemyBase()
{
	//AI���X�g��delete
	for (int i = 0;i < G_ENEMY_AILIST_MAX;++i) {

		for (int j = 0;j < m_ai_list[i].size();++j) {

			if (m_ai_list[i][j] != nullptr)delete m_ai_list[i][j];

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

	//���݂̏�Ԃɂ����铮��̍X�V
	UpdateState();

	//�A�j���[�V����(�p���p���摜)�l�̍X�V
	AnimationUpdate();

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

	//�U�����
	case EnemyStateType::Attack:
		EnemyAttack();
		next_state = ChangeStateFromAttack();
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
	if (m_state != next_state) {
		//next_scene���p�̕ϐ��ɓn���A��ԑJ��
		ChangeState(next_state);
	}
	

}

void EnemyBase::ChangeState()		//�G�l�~�[���s���������
{
	m_atk_time_count++;

	/*
		�G�l�~�[�̏�Ԃ̕ύX
	*/

	if (m_atk_time_count == 500 /*���ݒ�*/)
	{
		m_state = EnemyStateType::Attack;
		m_atk_time_count = 0;
	}

	/*
		11/29�@�c���R�����g�A�E�g
		m_centerX�����o�����������Ƃɂ���āA�G���[����
		m_centerX�����o�̑���ƂȂ���̂��K�v
	*/

	if (m_is_break == true)
	{
		//m_state = EnemyStateType::Rest;
	}
	else if (m_fatigue_gauge < Num_of_TakeaBreak)
	{
		m_state = EnemyStateType::Refuge;
	}
	//else if (m_pos.x + Distance_of_Maintain < trpplayer.GetPos().x)
	//{
	//	m_state = EnemyStateType::Chase;
	//}
	//else if (m_pos.x - Distance_of_Maintain > trpplayer.GetPos().x)
	//{
	//	m_state = EnemyStateType::Chase;
	//}
	//else
	//{
	//	m_state = EnemyStateType::Wait;	//�����̃G���[�̏ꍇ�ҋ@�֖߂�B
	//}
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

	case EnemyStateType::Attack:
		InitAttackState();
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

	m_state_saveflame = FlameTimer::GetNowFlame();

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

EnemyStateType EnemyBase::ChangeStateFromAttack()
{
	return EnemyStateType::Attack;
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

void EnemyBase::InitAttackState()
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
	for (int i = 0;i < G_ENEMY_AILIST_MAX;++i) {

		FileLoadTool::w_vector<int*> file = FileLoad::GetFileDataInt(file_name_ + FileLoadTool::ItoC(i + 1) + ".csv");

		//vector�z��
		for (int j = 1;j < file[i].size();++j) {

			//vector�g��
			m_ai_list[i].push_back(new EnemyAIParam());


			//��Ԃ��i�[
			if (*file[j][(int)EnemyAIArrayNum::State] < (int)EnemyStateType::EnemyStateTypeMax) {
				m_ai_list[i][j - 1]->e_state = (EnemyStateType)* file[j][(int)EnemyAIArrayNum::State];
			}
			else {
				m_ai_list[i][j - 1]->e_state = EnemyStateType::Wait;
			}

			//��Ԍp���������i�[
			if (*file[j][(int)EnemyAIArrayNum::Transition_Term] < (int)EnemyTransitionTerm::EnemyTransitionTerm_Max) {
				m_ai_list[i][j - 1]->e_transition_term = (EnemyTransitionTerm)* file[j][(int)EnemyAIArrayNum::Transition_Term];
			}
			else {
				m_ai_list[i][j - 1]->e_transition_term = EnemyTransitionTerm::FlameTime;
			}
			
			//�s�����x�l���i�[
			m_ai_list[i][j - 1]->e_speed_default	= *file[j][(int)EnemyAIArrayNum::Speed_Default];
			m_ai_list[i][j - 1]->e_speed_sleep		= *file[j][(int)EnemyAIArrayNum::Speed_Sleep];
			m_ai_list[i][j - 1]->e_speed_tired		= *file[j][(int)EnemyAIArrayNum::Speed_Tired];
			
			//��Ԍp�������Ŏg�p����l���i�[
			m_ai_list[i][j - 1]->e_transition_num	= *file[j][(int)EnemyAIArrayNum::Transition_Num];

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

		m_enemy_to_player_state = EnemytoPlayerState::Escape;

	}
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

	int cure_fatigue = Fatigue_Gauge_Max - m_fatigue_gauge;

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

	m_state = EnemyStateType::Attack;
	/*
		�e�G�l�~�[�U�����before_attack�̒��g��m_state�ɔ��f����
	*/
}

