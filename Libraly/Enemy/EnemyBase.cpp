#include "EnemyBase.h"
#include "../Player/TrpPlayer.h"

#define Num_of_TakeaBreak  100		//休憩をとる（疲労度の）数値
#define Limit_of_BreakTime 100		//MAXの休憩時間
#define Cure_of_SleepinessPoint 1	//時間回復する眠気の値
#define Cure_of_FatiguePoint 1		//時間回復する疲労の値
#define Distance_of_Maintain 100	//維持する適切な距離

//仮変数（定数）用意できたら消す分

const int player_pos_x = 100;
const int player_pos_y = 100;

//ここまで

TrpPlayer trpplayer;

EnemyBase::EnemyBase()
{
	m_Enemy_Id = Enemy::BossTypeMax;
	m_State = EnemyStateType::EnemyStateTypeMax;
	m_attack_repertory = EnemyAttackRepertory::VariableEnumrate_Type;
	m_enemy_to_player_state = EnemytoPlayerState::EtoPStateTypeMax;

	m_fatigue_gauge = NULL;
	m_sleep_gauge = NULL;
	m_time_of_break = 0;
	m_is_break = false;
	m_is_delete = true;
	m_is_hit_judge = false;
	//	仮決め
	m_enemy_pos.x = 500.0f;
	m_enemy_pos.y = 500.0f;
	m_speed = 10.0f;
}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Init()
{

}

void EnemyBase::Create()
{

}

void EnemyBase::Update()
{

}

void EnemyBase::Draw()
{

}

//	値渡し用

int EnemyBase::GetEnemyPosX()		//エネミーのx座標を取得
{
	return m_pos.x;
}

int EnemyBase::GetEnemyPosY()		//エネミーのy座標を取得
{
	return m_pos.y;
}

EnemyStateType EnemyBase::GetEnemyState()	//エネミーの状態を取得
{
	return m_State;
}

//	～ここまで～

void EnemyBase::UpdateState()		//エネミーの状態の更新	//必要？？
{
	switch (m_State)
	{
	case EnemyStateType::Idle:

		EnemyIdle();

		break;

	case EnemyStateType::Break:

		EnemyBreak();

		break;

	case EnemyStateType::Warn:

		EnemyMove();

		break;

	case EnemyStateType::Attack:

		EnemyAttack();

		break;

	case EnemyStateType::Refuge:

		EnemyRefuge();

		break;

	default:
		/*
			!!
		*/
		break;
	}
}

void EnemyBase::ChangeState()		//エネミーが行動する条件
{
	/*
		エネミーの状態の変更
	*/

	if (m_fatigue_gauge <= Num_of_TakeaBreak)
	{
		if (m_time_of_break < Limit_of_BreakTime)
		{
			m_is_break = true;
			m_State = EnemyStateType::Break;
			m_time_of_break++;
		}
		else if (m_is_break == true)
		{
			m_State = EnemyStateType::Refuge;
			m_time_of_break--;
			if (m_time_of_break == 0)
			{
				m_is_break == false;
			}
		}
	}

	/*
		プレイヤーの位置情報を取得して、適切な距離を保つ。
	*/
}

void EnemyBase::EnemyMove()			//エネミー移動
{
	/*
		通常状態のエネミー移動（適切な距離まで距離を詰める）
	*/

	if (m_pos.x < player_pos_x + Distance_of_Maintain || m_pos.x < player_pos_x - Distance_of_Maintain)
	{
		m_pos.x;		//書きかけ
	}

}

void EnemyBase::EnemyRefuge()		//疲労状態の逃走
{
	/*
		ピンチ状態のエネミー逃走
	*/



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

void EnemyBase::EnemyIdle()			//エネミー待機
{
	/*
		エネミーの待機（その場で待機アニメーション）
	*/



}

void EnemyBase::EnemyBreak()		//エネミー休憩
{
	/*
		エネミーの疲労待機（その場で疲労待機アニメーション）
	*/



}

int EnemyBase::GetSleepGauge()
{
	return m_sleep_gauge;
}

int EnemyBase::GetFatigueGauge()
{
	return m_fatigue_gauge;
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


