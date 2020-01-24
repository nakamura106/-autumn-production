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


//ここまで

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

	AllDrawEffect();
	
}

void EnemyBase::Init()
{
	
}

void EnemyBase::Update()
{
	//アニメーション(パラパラ画像)値の更新
	if (m_animation_stop != true) {
		AnimationUpdate();
	}

	//Stateの遷移
	//ChangeState();
	ObjectBase::Update();

	if (DataBank::Instance()->GetWavetype(WaveType::Wave1) != true)
	{
		//デバッグ用
		DebugKeyAction();

		//データバンクからのデータの取得
		DataGetUpdate();

		//ゲージの段階を保存、疲労ゲージ量によって自動ゲージ変動
		AutoChangeGageUpdate();

		//弾の制御
		BulletControl();

		//マップスクロールの位置計算
		CalcDrawPosition();

		//データバンクへの値受け渡し
		DataSetUpdate();

		// エフェクトアップデート関数まとめ
		AllUpdateEffect();

		//現在の状態における動作の更新
		//UpdateState();
		if (m_wave_state == WaveState::None) {
			//状態動作
			UpdateAIState();

		}
		else if (m_wave_state == WaveState::Change_Start) {
			//wave遷移中の動作(画面端に走っていく)
			WaveChangeState1();
		}
		else if (m_wave_state == WaveState::EnemyMoved) {
			WaveChangeState2();
		}
		else if (m_wave_state == WaveState::ItemGet) {
			//ゲーム開始
			if (FlameTimer::GetNowFlame(m_savetime_wavechange) > 120) {
				m_wave_state = WaveState::None;
			}
		}

		/*位置調整の更新*/
		MoveLimitUpdate();

		// 当たり判定更新関数
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
	//1.fを返すとプレイヤーにダメージ
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

//エネミーの状態の更新
void EnemyBase::UpdateState()
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
		return;

	//飛行状態
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

	
	//状態の変更
	if (m_state != next_state && m_stop_state_transition) {
		//next_sceneを専用の変数に渡し、状態遷移
		ChangeState(next_state);
	}
	

}

void EnemyBase::UpdateAIState()
{
	switch (m_state)
	{
		//待機状態
	case EnemyStateType::Wait:
		EnemyWait();
		break;

		//移動状態
	case EnemyStateType::Walk:
		EnemyMove();
		break;

		//攻撃1状態
	case EnemyStateType::Attack1:
		EnemyAttack1();
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
		EnemyMove();
		break;

		//追跡状態
	case EnemyStateType::Chase:
		EnemyMove();
		break;

		//睡眠状態(眠気度MAX)
	case EnemyStateType::Sleep:
		EnemySleep();
		return;

		//死亡状態(疲労度MAX)
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

	//AI状態遷移
	AITransitionUpdate();

}

void EnemyBase::AITransitionUpdate()
{
	//飛行状態の場合、状態遷移無し
	if (m_state == EnemyStateType::Fly)return;

	bool can_change_ai_state = false;

	switch (m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_transition_term)
	{
		//画面端まで移動
	case EnemyTransitionTerm::Straight:
		can_change_ai_state = AITransitionStraight();
		break;

		//プレイヤーを越える
	case EnemyTransitionTerm::PassPlayer:
		can_change_ai_state = AITransitionPassPlayer();
		break;

		//プレイヤーを前にした場合
	case EnemyTransitionTerm::FrontPlayer:
		can_change_ai_state = AITransitionFrontPlayer();
		break;

		//距離
	case EnemyTransitionTerm::Distance:
		can_change_ai_state = AITransitionDistance();
		break;

		//時間
	case EnemyTransitionTerm::FlameTime:
		can_change_ai_state = AITransitionFlameTime();
		break;

	default:
		break;
	}


	//状態遷移・AI変更を行う
	if (can_change_ai_state && !m_stop_state_transition) {

		CompleteChangeState();

	}

}

bool EnemyBase::AITransitionBase()
{
	//仮実装　画面は端まではいける
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

	//プレイヤーのx座標をゲット
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

	//プレイヤーのx座標をゲット
	
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

	//状態遷移条件値は移動距離でも判定するために存在(値0の場合は判定無し)
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
		//敵のゲージ量によってスピードが変化
		m_speed = (float)m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_speed_default;
		break;

	case GageState::Fatigue_State:
		//敵のゲージ量によってスピードが変化
		m_speed = (float)m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_speed_fatigue;
		break;

	case GageState::Sleep_State:
		//敵のゲージ量によってスピードが変化
		m_speed = (float)m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_speed_sleep;
		break;

	default:
		m_speed = (float)m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_speed_default;
		break;
	}

}

void EnemyBase::CompleteChangeState()
{
	//次の状態に行くための値を設定
	ChangeAIState();

	//ゲージ状態に合わせて速度を設定
	SetGageStateSpeed();

	//AIに合わせて向き変更
	ChangeAIDirection();

	//眠気・疲労状態遷移
	if (CheckSleepGageMax()) {

		if (m_now_wave >= m_max_wave) {
			//眠り状態へ遷移→クリア
			ChangeState(EnemyStateType::Sleep);
		}
		else {
			//wave遷移
			++m_now_wave;
			
			DataBank::Instance()->SetWaveState(WaveState::Change_Start);

			m_wave_state = WaveState::Change_Start;

		}
	}
	else if (CheckFatigueGageMax()) {
		//疲労ゲージが最大の場合、死亡状態へ遷移
		ChangeState(EnemyStateType::Dead);
	}
	else {
		//値に沿って状態遷移
		ChangeState(m_ai_list[static_cast<int>(m_now_ai)][m_now_ai_num]->e_state);
	}
}

void EnemyBase::AutoChangeGageUpdate()
{
	//ゲージの進行度を格納
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

	//ゲージ自動変動停止
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

	//疲労ゲージの段階
	switch (m_fatigue_gage_stage)
	{
	//0(最小)
	case EnemyGageStage::Zero:
		sleep_down = M_AUTO_SLEEP_UP_MAX_SPEED;
		break;

	//1段階目　～1/4
	case EnemyGageStage::Quarter:
		//眠気減少：高速
		sleep_down = M_AUTO_SLEEP_UP_HIGH_SPEED;
		break;

	//2段階目　～1/2
	case EnemyGageStage::Half_Down:
		//眠気減少：中速
		sleep_down = M_AUTO_SLEEP_UP_MEDIUM_SPEED;
		break;

	//3段階目　～3/4
	case EnemyGageStage::Half_Up:
		//眠気減少：低速
		sleep_down = M_AUTO_SLEEP_UP_LOW_SPEED;
		fatigue_up = M_AUTO_FATIGUE_DOWN_LOW_SPEED;
		break;

	//4段階目　～最大
	case EnemyGageStage::Almost:
		//眠気減少：停止、疲労増加：低速
		fatigue_up = M_AUTO_FATIGUE_DOWN_LOW_SPEED;
		break;

	//Max(最大)
	case EnemyGageStage::Max:
		//敵死亡
		break;

	default:
		break;
	}

	//ゲージ変動
	UpFatigueGage(fatigue_up);

	if (m_stop_auto_sleep_time <= 0) {
		m_is_debuff = false;
		DownSleepGage(sleep_down);
	}
	

	//ゲージのコントロール
	GaugeLimitControl();

}

int EnemyBase::GageStageCalc(float now_gage_, float max_gage_, int gage_stage_num_)
{
	//ゲージが最大の場合、段階数+1の値を返す
	if (now_gage_ >= max_gage_) {
		++gage_stage_num_;
		return gage_stage_num_;
	}

	//ゲージが0(最小)の場合、0を返す
	if (now_gage_ == 0.f) {
		return 0;
	}

	//ゲージの段階数に応じた現在の進行段階を返す
	return static_cast<int>(now_gage_ / (max_gage_ / static_cast<float>(gage_stage_num_))) + 1;
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
	
}

void EnemyBase::ChangeState(EnemyStateType next_state_)
{
	//状態変更
	m_state = next_state_;

	//全状態共通の初期化関数
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

	//現在の状態を格納
	m_savetime_state = FlameTimer::GetNowFlame();
	m_state_save_pos_x = m_map_pos;

	//プレイヤーがどちらの方向にいるのかを格納
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
		//使用する画像の変更(以下同じ)
		if (m_is_flying == true) {
			//飛行時
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_SkyWaitLeft;
		}
		else if (m_fatigue_gage_stage >= EnemyGageStage::Half_Up) {
			//疲労状態
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_FatigueLeft;
		}
		else {
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_WaitLeft;
		}
	}
	else {
		if (m_is_flying == true) {
			//飛行時
			m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_SkyWaitRight;
		}
		else if (m_fatigue_gage_stage >= EnemyGageStage::Half_Up) {
			//疲労状態
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
	//方向をプレイヤーの側にする
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
		//終了

		DataBank::Instance()->SetWaveState(WaveState::ItemGet);

		m_wave_state = WaveState::ItemGet;

		m_savetime_wavechange = FlameTimer::GetNowFlame();

		m_state = EnemyStateType::Wait;
		InitWaitState();
	}
}

//Csv読み込み関数
void EnemyBase::LoadAIData(std::string file_name_)
{
	//１～１０の基本配列
	for (int i = 0;i < static_cast<int>(EnemyAIType::EnemyAIType_Max);++i) {

		std::string f_name = file_name_ + std::to_string(i + 1) + ".csv";

		FileLoadTool::w_vector<int*> file = FileLoad::GetFileDataInt(f_name);

		//vector配列
		for (int j = 1;j < static_cast<int>(file.size());++j) {

			//vector拡張
			m_ai_list[i].push_back(new EnemyAIParam());


			//状態を格納
			if (*file[j][static_cast<int>(EnemyAIArrayNum::State)] < static_cast<int>(EnemyStateType::EnemyStateType_Max)) {
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
			m_ai_list[i][j - 1]->e_speed_fatigue = *file[j][static_cast<int>(EnemyAIArrayNum::Speed_Tired)];

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



//エネミー移動
void EnemyBase::EnemyMove()			
{
	/*
		通常状態のエネミー移動（適切な距離まで距離を詰める）
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
	//データバンクに値を入れる
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
		//ドラミング中の場合、無効化
		return;
	}

	//当たり判定
	switch (ravel_)
	{
	//プレイヤー
	case ObjectRavel::Ravel_Player:
		break;

	//プレイヤー弾①
	case ObjectRavel::Ravel_PlayerBullet:
		//眠気増加
		UpSleepGage(hit_use_atk_);
		m_stop_auto_sleep_time = M_STOP_AUTO_SLEEP_TIME_HITBULLET;
		break;

	//プレイヤー弾②
	case ObjectRavel::Ravel_PlayerBullet2:
		//疲労回復
		DownFatigueGage(hit_use_atk_);
		m_stop_auto_sleep_time = M_STOP_AUTO_SLEEP_TIME_HITBULLET;
		break;

	//プレイヤー弾③
	case ObjectRavel::Ravel_PlayerBullet3:
		UpFatigueGage(hit_use_atk_);
		m_stop_auto_sleep_time = M_STOP_AUTO_SLEEP_TIME_HITBULLET;
		break;

	//プレイヤー弾④
	case ObjectRavel::Ravel_PlayerBullet4:
		m_stop_auto_sleep_time = static_cast<int>(hit_use_atk_);
		break;

	default:
		break;
	}
}

bool EnemyBase::IsMoveLimitLeft()
{
	//位置調整左
	if (m_map_pos <= 0.f) {
		return true;
	}

	return false;
}

bool EnemyBase::IsMoveLimitRight()
{
	//位置調整右
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
	//疲労状態
	if (m_fatigue_gage_stage > m_sleep_gage_stage && m_fatigue_gage_stage >= EnemyGageStage::Half_Up) {//段階3はゲージ半分以上
		return GageState::Fatigue_State;
	}
	
	//眠気(イライラ)状態
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
	//ゲームクリアフラグをDataBankにセット
	if (FlameTimer::GetNowFlame(m_savetime_end) >= GAMECLEAR_FLAME) {

		DataBank::Instance()->SetIsGameClear(true);

	}
}

void EnemyBase::EnemyFly()
{
}

void EnemyBase::EnemyDead()
{
	//ゲームオーバーフラグをDataBankにセット
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

	//最小値で止める
	if (m_sleep_gauge <= 0.f) {
		m_sleep_gauge = 0.f;
	}
}

void EnemyBase::DownFatigueGage(float down_num_)
{
	m_fatigue_gauge -= down_num_;

	//最小値で止める
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

	//発射位置調整
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

	//弾の発射位置を取得
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

	//通常弾生成
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

	//最大値で止める
	if (m_sleep_gauge >= Sleep_Gauge_Max) {

		m_sleep_gauge = Sleep_Gauge_Max;

		//1分間の自動回復停止
		m_stop_auto_sleep_time = 3600;

	}

}

void EnemyBase::UpFatigueGage(float up_num_)
{
	m_fatigue_gauge += up_num_;

	//最大値で止める
	if (m_fatigue_gauge >= Fatigue_Gauge_Max) {

		m_fatigue_gauge = Fatigue_Gauge_Max;

	}
}

void EnemyBase::ChangeWave()
{

}

