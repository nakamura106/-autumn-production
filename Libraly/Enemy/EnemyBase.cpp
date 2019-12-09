#include "EnemyBase.h"
#include "../Player/TrpPlayer.h"
#include"../Engine/FileLoader.h"
#include"../Engine/Input.h"
#include<stdlib.h>

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
	//bullet解放
	for (auto& i : bullet_list) {
		delete i;
		i = nullptr;
	}
	std::vector<EnemyBullet*>().swap(bullet_list);

	//AIリストのdelete
	for (int i = 0;i < (int)EnemyAIType::EnemyAIType_Max;++i) {

		for (int j = 0;j < static_cast<int>(m_ai_list[i].size());++j) {

			if (m_ai_list[i][j] != nullptr)delete m_ai_list[i][j];

		}
	}

}

void EnemyBase::Draw()
{
	//エネミーの描画
	ObjectBase::Draw();

	//弾の描画
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
	//Stateの遷移
	//ChangeState();

	//デバッグ用
	DebugKeyAction();

	//現在の状態における動作の更新
	UpdateState();

	//アニメーション(パラパラ画像)値の更新
	AnimationUpdate();

	//弾の制御
	BulletControl();

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

	//攻撃1状態
	case EnemyStateType::Attack1:
		EnemyAttack1();
		next_state = ChangeStateFromAttack1();
		break;

	//攻撃2状態
	case EnemyStateType::Attack2:
		EnemyAttack2();
		break;

	//攻撃3状態
	case EnemyStateType::Attack3:
		EnemyAttack3();
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
	if (m_state != next_state && m_can_state_transition) {
		//next_sceneを専用の変数に渡し、状態遷移
		ChangeState(next_state);
	}
	

}

void EnemyBase::UpdateAIState()
{
	bool can_change_ai_state = false;

	switch (m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_transition_term)
	{
		//画面端まで移動
	case EnemyTransitionTerm::Straight:
		can_change_ai_state = TransitionStraight();
		break;

		//プレイヤーを越える
	case EnemyTransitionTerm::PassPlayer:
		can_change_ai_state = TransitionPassPlayer();
		break;

		//プレイヤーを前にした場合
	case EnemyTransitionTerm::FrontPlayer:
		can_change_ai_state = TransitionFrontPlayer();
		break;

		//距離
	case EnemyTransitionTerm::Distance:
		can_change_ai_state = TransitionDistance();
		break;

		//時間
	case EnemyTransitionTerm::FlameTime:
		can_change_ai_state = TransitionFlameTime();
		break;

	default:
		break;
	}

	if (can_change_ai_state) {
		//次の状態へ
		ChangeAIState();
	}
}

bool EnemyBase::TransitionStraight()
{
	//仮実装　画面は端まではいける
	if ((m_pos.x <= 0.f || (m_pos.x + m_draw_param.tex_size_x) > 1920.f)
		&& m_animation_end) 
	{
		return true;
	}

	return false;
}

bool EnemyBase::TransitionPassPlayer()
{
	//プレイヤーのx座標をゲット

	return false;
}

bool EnemyBase::TransitionFrontPlayer()
{
	//プレイヤーのx座標をゲット
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

void EnemyBase::ChangeAIState()		//エネミーが行動する条件
{
	if (static_cast<int>(m_now_ai) >= static_cast<int>(EnemyAIType::EnemyAIType_Max)) {
		//エラー:アクセスする場所が存在しない
		return;
	}

	//使用中AIを次の状態に進行
	++m_now_ai_num;
	
	if (m_now_ai_num >= static_cast<int>(m_ai_list[static_cast<int>(m_now_ai)].size())) {
		//aiの変更
		//ここで、AI条件分岐関数を呼び出す
		EnemyAIType next_ai = ChangeAIType();

		//返ってきた値が無効値の場合、「AI1」にする
		if (next_ai >= EnemyAIType::EnemyAIType_Max) {
			next_ai = EnemyAIType::AI1;
		}

		//AI変更
		m_now_ai = next_ai;
		m_now_ai_num = 0;

	}

	//状態遷移
	ChangeState(m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_state);
	
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

	//現在の状態を格納
	m_state_saveflame = FlameTimer::GetNowFlame();
	m_state_save_pos_x = m_pos.x;

	//プレイヤーがどちらの方向にいるのかを格納
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
	//１～１０の基本配列
	for (int i = 0;i < static_cast<int>(EnemyAIType::EnemyAIType_Max);++i) {

		FileLoadTool::w_vector<int*> file = FileLoad::GetFileDataInt(file_name_ + FileLoadTool::ItoC(i + 1) + ".csv");

		//vector配列
		for (int j = 1;j < static_cast<int>(file[i].size());++j) {

			//vector拡張
			m_ai_list[i].push_back(new EnemyAIParam());


			//状態を格納
			if (*file[j][static_cast<int>(EnemyAIArrayNum::State)] < static_cast<int>(EnemyStateType::EnemyStateTypeMax)) {
				m_ai_list[i][j - 1]->e_state = (EnemyStateType)* file[j][static_cast<int>(EnemyAIArrayNum::State)];
			}
			else {
				m_ai_list[i][j - 1]->e_state = EnemyStateType::Wait;
			}

			//状態継続条件を格納
			if (*file[j][static_cast<int>(EnemyAIArrayNum::Transition_Term)] < static_cast<int>(EnemyTransitionTerm::EnemyTransitionTerm_Max)) {
				m_ai_list[i][j - 1]->e_transition_term = (EnemyTransitionTerm)* file[j][static_cast<int>(EnemyAIArrayNum::Transition_Term)];
			}
			else {
				m_ai_list[i][j - 1]->e_transition_term = EnemyTransitionTerm::FlameTime;
			}

			//行動速度値を格納
			m_ai_list[i][j - 1]->e_speed_default = *file[j][static_cast<int>(EnemyAIArrayNum::Speed_Default)];
			m_ai_list[i][j - 1]->e_speed_sleep = *file[j][static_cast<int>(EnemyAIArrayNum::Speed_Sleep)];
			m_ai_list[i][j - 1]->e_speed_tired = *file[j][static_cast<int>(EnemyAIArrayNum::Speed_Tired)];

			//状態継続条件で使用する値を格納
			m_ai_list[i][j - 1]->e_transition_num = *file[j][static_cast<int>(EnemyAIArrayNum::Transition_Num)];

			//向き情報を格納
			if (*file[j][static_cast<int>(EnemyAIArrayNum::Enemy_Direction)] < static_cast<int>(EnemyDirection::EnemyDirection_Max)) {
				m_ai_list[i][j - 1]->e_direction = static_cast<EnemyDirection>(*file[j][static_cast<int>(EnemyAIArrayNum::Enemy_Direction)]);
			}
			else {
				m_ai_list[i][j - 1]->e_direction = EnemyDirection::Same;
			}
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

		//m_enemy_to_player_state = EnemytoPlayerState::Escape;

	}
}

void EnemyBase::EnemyAttack1()		//エネミー攻撃
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
		//弾の更新
		bullet_list[i]->Update();

		//弾のis_deleteがtrueの場合、弾消滅
		if (bullet_list[i]->GetIsDelete()) {
			//メモリ解放
			delete bullet_list[i];

			//弾を消滅
			bullet_list.erase(bullet_list.begin() + i);

		}
	}
}

void EnemyBase::DebugKeyAction()
{
	static bool s_is_key = false;

	if (GetKey(E_KEY)) {
		if (!s_is_key) {
			//待ち状態に遷移
			ChangeState(EnemyStateType::Wait);
			m_can_state_transition = !m_can_state_transition;
		}
		s_is_key = true;
	}
	else {
		s_is_key = false;
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

	int cure_fatigue = (int)(Fatigue_Gauge_Max - m_fatigue_gauge);

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

	m_state = EnemyStateType::Attack1;
	/*
		各エネミー攻撃後にbefore_attackの中身をm_stateに反映する
	*/
}

