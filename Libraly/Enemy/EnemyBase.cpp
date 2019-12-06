#include "EnemyBase.h"
#include "../Player/TrpPlayer.h"
#include"../Engine/FileLoader.h"

#define Num_of_TakeaBreak  100		//休憩をとる（疲労度の）数値
#define Refuge_Time	100				//逃げ回る時間
#define Limit_of_BreakTime 100		//MAXの休憩時間
#define Cure_of_SleepinessPoint 1	//時間回復する眠気の値
#define Cure_of_FatiguePoint 1		//時間回復する疲労の値
#define Distance_of_Maintain 100	//維持する適切な距離

#define Fatigue_Gauge_Max 100		//疲労ゲージ上限
#define Sleep_Gauge_Max	100			//睡眠ゲージ上限

#define Attack_Interval 100			//攻撃感覚

//ここまで

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

	//	仮決め
	m_pos.x = M_INIT_POS_X;
	m_pos.y = M_INIT_POS_Y;
	

	//描画情報格納
	m_draw_param.tu				= 1;
	m_draw_param.tv				= 1;
	m_draw_param.category_id	= TEXTURE_CATEGORY_GAME;
	m_draw_param.texture_id		= GameCategoryTextureList::GameEnemy_WalkLeft;
	m_draw_param.tex_size_x		= M_ENEMY_SYZE;
	m_draw_param.tex_size_y		= M_ENEMY_SYZE;

	//アニメーション情報格納
	m_anim_param.change_flame	= M_ANIM_FLAME;
	m_anim_param.split_all		= M_ANIM_TEX_ALL;
	m_anim_param.split_width	= M_ANIM_TEX_WIDTH;
	m_anim_param.split_height	= M_ANIM_TEX_HEIGHT;

	//saveflame(フレーム数計測用変数)
	m_state_saveflame = 0;

	for (int i = 0;i < G_ENEMY_AILIST_MAX;++i) {
		m_ai_list[i].clear();
	}
	
}

EnemyBase::~EnemyBase()
{
	//AIリストのdelete
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
	//Stateの遷移
	//ChangeState();

	//現在の状態における動作の更新
	UpdateState();

	//アニメーション(パラパラ画像)値の更新
	AnimationUpdate();

}


EnemyStateType EnemyBase::GetEnemyState()	//エネミーの状態を取得
{
	return m_state;
}

//	～ここまで～

void EnemyBase::UpdateState()		//エネミーの状態の更新
{
	//次の状態を示す変数
	EnemyStateType next_state = m_state;

	switch (m_state)
	{
	//待機状態
	case EnemyStateType::Wait:
		EnemyWait();
		next_state = ChangeStateFromWait();
		break;

	//移動状態
	case EnemyStateType::Walk:
		EnemyMove();
		next_state = ChangeStateFromWalk();
		break;

	//攻撃状態
	case EnemyStateType::Attack:
		EnemyAttack();
		next_state = ChangeStateFromAttack();
		break;

	//逃走状態(ゲージが一定以下の場合逃げる処理)
	case EnemyStateType::Refuge:
		EnemyRefuge();
		next_state = ChangeStateFromRefuge();
		break;

	//追跡状態
	case EnemyStateType::Chase:
		next_state = ChangeStateFromChase();
		break;

	//睡眠状態(眠気度MAX)
	case EnemyStateType::Sleep:

		break;

	default:
		/*
			!!
		*/
		break;
	}

	
	//状態の変更
	if (m_state != next_state) {
		//next_sceneを専用の変数に渡し、状態遷移
		ChangeState(next_state);
	}
	

}

void EnemyBase::ChangeState()		//エネミーが行動する条件
{
	m_atk_time_count++;

	/*
		エネミーの状態の変更
	*/

	if (m_atk_time_count == 500 /*仮設定*/)
	{
		m_state = EnemyStateType::Attack;
		m_atk_time_count = 0;
	}

	/*
		11/29　田中コメントアウト
		m_centerXメンバが消えたことによって、エラー発生
		m_centerXメンバの代わりとなるものが必要
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
	//	m_state = EnemyStateType::Wait;	//処理のエラーの場合待機へ戻る。
	//}
}

void EnemyBase::ChangeState(EnemyStateType next_state_)
{
	//状態変更
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
	//１～１０の基本配列
	for (int i = 0;i < G_ENEMY_AILIST_MAX;++i) {

		FileLoadTool::w_vector<int*> file = FileLoad::GetFileDataInt(file_name_ + FileLoadTool::ItoC(i + 1) + ".csv");

		//vector配列
		for (int j = 1;j < file[i].size();++j) {

			//vector拡張
			m_ai_list[i].push_back(new EnemyAIParam());


			//状態を格納
			if (*file[j][(int)EnemyAIArrayNum::State] < (int)EnemyStateType::EnemyStateTypeMax) {
				m_ai_list[i][j - 1]->e_state = (EnemyStateType)* file[j][(int)EnemyAIArrayNum::State];
			}
			else {
				m_ai_list[i][j - 1]->e_state = EnemyStateType::Wait;
			}

			//状態継続条件を格納
			if (*file[j][(int)EnemyAIArrayNum::Transition_Term] < (int)EnemyTransitionTerm::EnemyTransitionTerm_Max) {
				m_ai_list[i][j - 1]->e_transition_term = (EnemyTransitionTerm)* file[j][(int)EnemyAIArrayNum::Transition_Term];
			}
			else {
				m_ai_list[i][j - 1]->e_transition_term = EnemyTransitionTerm::FlameTime;
			}
			
			//行動速度値を格納
			m_ai_list[i][j - 1]->e_speed_default	= *file[j][(int)EnemyAIArrayNum::Speed_Default];
			m_ai_list[i][j - 1]->e_speed_sleep		= *file[j][(int)EnemyAIArrayNum::Speed_Sleep];
			m_ai_list[i][j - 1]->e_speed_tired		= *file[j][(int)EnemyAIArrayNum::Speed_Tired];
			
			//状態継続条件で使用する値を格納
			m_ai_list[i][j - 1]->e_transition_num	= *file[j][(int)EnemyAIArrayNum::Transition_Num];

		}
	}
}



void EnemyBase::EnemyMove()			//エネミー移動
{
	/*
		通常状態のエネミー移動（適切な距離まで距離を詰める）
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
		敵が自分より右方向へ遠くにいる場合の追跡
	*/

	m_pos.x + m_speed;

	m_enemy_to_player_state = EnemytoPlayerState::Separated;
}

void EnemyBase::EnemyChase_L()
{
	/*
		敵が自分より左方向へ遠くにいる場合の追跡
	*/

	m_pos.x - m_speed;

	m_enemy_to_player_state = EnemytoPlayerState::Separated;
}

#endif

void EnemyBase::EnemyRefuge()		//疲労状態の逃走
{
	/*
		ピンチ状態のエネミー逃走
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
			enemy逃げる処理
		*/

		m_enemy_to_player_state = EnemytoPlayerState::Escape;

	}
}

void EnemyBase::EnemyAttack()		//エネミー攻撃
{
	/*
		敵からプレイヤーへの状態に応じて攻撃種を変更
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

void EnemyBase::EnemyWait()			//エネミー待機
{
	/*
		エネミーの待機（その場で待機アニメーション）
	*/



}

void EnemyBase::EnemyChase()
{



}

void EnemyBase::EnemyRest()		//エネミー休憩
{
	/*
		エネミーの疲労待機（その場で疲労待機アニメーション）
	*/

	int cure_fatigue = Fatigue_Gauge_Max - m_fatigue_gauge;

	if (cure_fatigue > 0)
	{
		m_fatigue_gauge -= Cure_of_FatiguePoint * 5;	//だいたい通常回復の五倍くらい？
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
		各エネミー攻撃後にbefore_attackの中身をm_stateに反映する
	*/
}

