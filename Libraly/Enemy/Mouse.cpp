#include "Mouse.h"

//定数値は仮決め

#define Num_of_TakeaBreak  100		//休憩をとる（疲労度の）数値
#define Limit_of_BreakTime 100		//MAXの休憩時間
#define Cure_of_SleepinessPoint 1	//時間回復する眠気の値
#define Cure_of_FatiguePoint 1		//時間回復する疲労の値
#define Distance_of_Maintain 100	//維持する適切な距離
#define Gauge_Variable 100			//ゲージ調節用
#define Attack_Interval	100			//攻撃間隔

Hedgehog::Hedgehog()
{
	m_Enemy_Id = Enemy::Hedgehog;
	m_State = EnemyStateType::Warn;
	m_attack_repertory = AttackRepertoryofHedgeHog::AttackRepertoryMax;
	m_enemy_to_player_state = EnemytoPlayerState::EtoPStateTypeMax;
	m_fatigue_gauge = Gauge_Variable;
	m_sleep_gauge = Gauge_Variable;
	m_is_delete = false;

	m_time_of_break = 0;
	m_is_break = false;
	m_is_hit_judge = false;
	//	仮決め
	m_pos.x = 500.0f;
	m_pos.y = 500.0f;
	m_speed = 10.0f;
}

Hedgehog::~Hedgehog()
{

}


void Hedgehog::ChangeState()
{

}

void Hedgehog::EnemyMove()
{

}

void Hedgehog::EnemyRefuge()
{

}

void Hedgehog::EnemyAttack()
{
	/*
		敵からプレイヤーへの状態に応じて攻撃種を変更
	*/

	switch (m_enemy_to_player_state)
	{
	case EnemytoPlayerState::Separated:

		m_attack_repertory = AttackRepertoryofHedgeHog::Rush;
		Rush();
		break;

	case EnemytoPlayerState::Close:

		m_attack_repertory = AttackRepertoryofHedgeHog::HeadButt;
		Headbutt();
		break;

	case EnemytoPlayerState::Escape:

		m_attack_repertory = AttackRepertoryofHedgeHog::NeedleFire;
		NeedleFire();
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

void Hedgehog::EnemyIdle()
{

}

void Hedgehog::EnemyBreak()
{

}

//	ハリネズミAttackの処理（仮）

void Headbutt()
{
	/*
		頭突き処理
		プレイヤー方向に頭突き
		ｘ方向へ素早く移動して元の座標まで戻る
		頭突き距離　150
	*/

	


}

void Rush()
{
	/*
		突進処理
		等加速度で走っていく
		移動距離仮決め　800
	*/



}

void NeedleFire()
{
	/*
		とげ発射処理
		とげ発射方向　－＞　プレイヤーの座標
		追尾　なし
		発射　3way 2回くらい？
	*/



}

