#include "EnemyBase.h"
#include "Object/Definition.h"

#define Num_of_TakeaBreak  100

int EnemyBase::GetEnemyPosX()		//エネミーのx座標を取得
{
	return m_pos.x;
}

int EnemyBase::GetEnemyPosY()		//エネミーのy座標を取得
{
	return m_pos.y;
}

void EnemyBase::UpdateState()		//エネミーの状態の更新
{
	switch (m_State) 
	{
	case Idle:

		EnemyIdle();

		break;

	case Break:

		EnemyBreak();

		break;

	case Warn:

		EnemyMove();
		
		break;

	case Attack:

		EnemyAttack();

		break;

	case Refuge:

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
}

void EnemyBase::EnemyMove()			//エネミー移動
{
	/*
		通常状態のエネミー移動
	*/
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
		プレイヤーの状態に応じて攻撃種を変更
	*/
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

EnemyBase::EnemyBase()
{
	m_Enemy_Id = Enemy::BossTypeMax;
	m_State = EnemyStateType::MaxStateType;
}

EnemyBase::~EnemyBase()
{

}
