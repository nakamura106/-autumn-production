#include "Mouse.h"
#include "../Player/TrpPlayer.h"

//定数値は仮決め

#define Num_of_TakeaBreak  100		//休憩をとる（疲労度の）数値
#define Refuge_Time	100				//逃げ回る時間
#define Limit_of_BreakTime 100		//MAXの休憩時間
#define Cure_of_SleepinessPoint 1	//時間回復する眠気の値
#define Cure_of_FatiguePoint 1		//時間回復する疲労の値
#define Distance_of_Maintain 100	//維持する適切な距離

#define Fatigue_Gauge_Max 100		//疲労ゲージ上限
#define Sleep_Gauge_Max	100			//睡眠ゲージ上限

#define Attack_Interval 100			//攻撃感覚
#define HedgeHog_Speed 10			//読んで字の如く

TrpPlayer* trpplayer;

HedgeHog::HedgeHog()
{
	m_enemy_id = EnemyID::BossTypeMax;
	m_state = EnemyStateType::EnemyStateTypeMax;
	m_attack_repertory = AttackRepertoryofHedgeHog::None;
	m_enemy_to_player_state = EnemytoPlayerState::EtoPStateTypeMax;

	m_fatigue_gauge = NULL;
	m_sleep_gauge = NULL;
	m_time_of_break = 0;
	m_refuge_time = Refuge_Time;
	m_is_break = false;
	m_is_delete = true;
	m_is_hit_judge = false;
	m_is_speed_up = false;
	m_speed = 10.0f;
}

HedgeHog::~HedgeHog()
{
}

/*
HedgeHog::~HedgeHog()
{

}

void HedgeHog::Init()
{

}

void HedgeHog::Create()
{

}

void HedgeHog::Update()
{

}

void HedgeHog::Draw()
{

}
*/

void HedgeHog::EnemyAttack()		//エネミー攻撃
{
	/*
		敵からプレイヤーへの状態に応じて攻撃種を変更
	*/

	switch (m_enemy_to_player_state)
	{
	case EnemytoPlayerState::Separated:

		Rush();
		m_attack_repertory = AttackRepertoryofHedgeHog::Rush;

		break;

	case EnemytoPlayerState::Close:

		Headbutt();
		m_attack_repertory = AttackRepertoryofHedgeHog::HeadButt;

		break;

	case EnemytoPlayerState::Escape:

		NeedleFire();
		m_attack_repertory = AttackRepertoryofHedgeHog::NeedleFire;

		break;

	case EnemytoPlayerState::Pursue:

		m_attack_repertory = AttackRepertoryofHedgeHog::None;

		break;


	default:
		/*
			!!
		*/
		break;
	}

}


//	ハリネズミAttackの処理（仮）

void HedgeHog::Headbutt()
{
	/*
		頭突き処理
		プレイヤー方向に頭突き
		ｘ方向へ素早く移動して元の座標まで戻る
		頭突き距離　150
	*/

	//	アニメーション変更

}

void HedgeHog::Rush()
{
	/*
		突進処理
		一定加速後同じ速度で減速
	*/

	//	アニメーション変更

}

void HedgeHog::NeedleFire()
{
	/*
		とげ発射処理
		とげ発射方向　－＞　プレイヤーの座標
		追尾　なし
		発射　3way 2回くらい？
	*/

	//	アニメーション変更ある？

}

