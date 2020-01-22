#include "Mouse.h"
#include "../Player/TrpPlayer.h"

//定数値は仮決め

#define Num_of_TakeaBreak  100		//休憩をとる（疲労度の）数値
#define Refuge_Time	100				//逃げ回る時間
#define Limit_of_BreakTime 100		//MAXの休憩時間
#define Cure_of_FatiguePoint 1		//時間回復する疲労の値
#define Distance_of_Maintain 100	//維持する適切な距離
//
//#define Fatigue_Gauge_Max 100		//疲労ゲージ上限
//#define Sleep_Gauge_Max	100			//睡眠ゲージ上限

#define Attack_Interval 100			//攻撃感覚
#define HedgeHog_Speed 10			//読んで字の如く

TrpPlayer* trpplayer;

HedgeHog::HedgeHog()
	:EnemyBase(2.f, EnemyID::Hedgehog, 1, 512.f)
{
	//Csvファイル読み込み
	LoadAIData(M_AIDataFileName);

	//使用するAI番号の設定
	SetAIType();

	//状態設定
	CompleteChangeState();

	m_is_speed_up = false;
	m_do_bullet = false;
	SetRectangle();
	m_shot_adjust.x = M_NEEDLE_ADJUST_X;
	m_shot_adjust.y = M_NEEDLE_ADJUST_Y;

}

HedgeHog::~HedgeHog()
{

}

void HedgeHog::Init()
{
	
}


void HedgeHog::SetRectangle()
{
	m_rect_param.shift_x = 250.f;//105.0f;
	m_rect_param.shift_y = 440.0f;
	m_rect_param.width = 829.0f;
	m_rect_param.height = 561.0f;
}

void HedgeHog::EnemyAttack1()		//エネミー攻撃
{
	/*
		突進処理
		一定加速後同じ速度で減速
	*/

	if (GetAnimationTexNum() > M_ATTACK1_ANIM_TEX_NUM) {
		m_speed /= M_DASHATTACK_SPEED_CHANGE_NUM;
	}
	else {
		m_speed *= M_DASHATTACK_SPEED_CHANGE_NUM;
	}

	EnemyBase::EnemyMove();

}

void HedgeHog::EnemyAttack2()
{
	/*
		とげ発射処理
		とげ発射方向　－＞　プレイヤーの座標
		追尾　なし
		発射　3way 2回くらい？
	*/
	if (GetAnimationTexNum() > M_ATTACK2_ANIM_TEX_NUM && !m_do_bullet) {
		//発射したかどうかのフラグをON
		m_do_bullet = true;

		//弾発射
		CreateBullet(static_cast<Direction>(m_direction), m_speed);

	}
}

void HedgeHog::EnemyAttack3()
{
	int num = GetAnimationTexNum();

	if (num == M_ATTACK3_ANIM_TEX_NUM) {
		EnemyMove();
	}
}

EnemyStateType HedgeHog::ChangeStateFromWait()
{
	//使用していない関数であり、将来的に消去するためマジックナンバーのまま
	if (GetStateSaveFlame() > 120 && m_is_animation_end) {

		ChangeDirection();

		return EnemyStateType::Walk;
	}

	return EnemyStateType::Wait;
}

EnemyStateType HedgeHog::ChangeStateFromWalk()
{
	//使用していない関数であり、将来的に消去するためマジックナンバーのまま
	if (GetStateSaveFlame() > 60 && m_is_animation_end) {
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
	if (m_is_animation_end) {
		m_do_bullet = false;
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
	//Enemyの位置や向き、プレイヤーとの関係によって
	//次に使用するAIが変化する

	//AI1→初期AI
	//AI2→待機・移動
	//AI3→自動動作
	//AI4→追跡・待機
	//AI5→往復突進
	//AI6→トゲ発射
	//AI7→頭突き

	EnemyAIType now_ai = GetNowAI();

	//プレイヤーとエネミーの距離
	int p_e_distance = fabsf(m_player_center_pos - m_map_pos);
	
	//乱数を入手
	int random = RandomTool::GetRandom();


	if (now_ai == EnemyAIType::AI5 ||
		now_ai == EnemyAIType::AI6 ||
		now_ai == EnemyAIType::AI7) {

		//3種類の攻撃の後は必ず休む
		return EnemyAIType::AI3;

	}

	if (m_fatigue_gage_stage == 0&&m_sleep_gage_stage==0) {

		return EnemyAIType::AI2;

	}

	//追跡のみを行う、Player散策AI
	if (p_e_distance >= 700.f) {

		return EnemyAIType::AI4;

	}
	else {
		//3種類の攻撃をランダムに繰り出す
		switch (random % 3)
		{
		case 0:
			return EnemyAIType::AI5;

		case 1:
			return EnemyAIType::AI6;

		case 2:
			return EnemyAIType::AI7;
		}
	}

	return EnemyAIType::AI1;
}


void HedgeHog::InitAllState()
{
	EnemyBase::InitAllState();
}

/*/*/