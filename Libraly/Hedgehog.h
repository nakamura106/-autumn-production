//#pragma once
//#include "EnemyBase/EnemyBase.h"
//
////!~
//
//typedef enum AttackRepertoryofHedgeHog
//{
//	Rush,
//	HeadButt,
//	NeedleFire,
//	None,
//	AttackRepertoryMax,
//}EnemyAttackRepertory;
//
////~!
//
//class Hedgehog :public EnemyBase 
//{
//public:
//
//	virtual void Init() = 0;
//	virtual void Create() = 0;
//	virtual void Update() = 0;
//	virtual void Draw() = 0;
//
//	virtual int GetEnemyPosX();
//	virtual int GetEnemyPosY();
//	virtual EnemyStateType GetEnemyState();
//
//	virtual void UpdateState();
//	virtual void ChangeState();
//
//	virtual void EnemyMove();
//	virtual void EnemyRefuge();
//	virtual void EnemyAttack();
//	virtual void EnemyIdle();
//	virtual void EnemyBreak();
//
//	virtual int GetSleepGauge();
//	virtual int GetFatigueGauge();
//
//	virtual void CureSleepiness();
//	virtual void CureFatigue();
//
//protected:
//
//	float m_sleep_gauge;	//眠りゲージ
//	float m_fatigue_gauge;	//疲労ゲージ
//	int m_TimeofBreak;		//休憩時間
//	bool m_IsBreak;			//休憩しているか
//	bool m_IsHitJudge;		//当たり判定が存在するか
//	int m_speed;			//スピード
//
//
//	Enemy m_Enemy_Id;
//	EnemyStateType m_State;
//	AttackRepertoryofHedgeHog m_attack_repertory;
//	EnemytoPlayerState m_enemy_to_player_state;
//
//public:
//	Hedgehog();
//	~Hedgehog();
//
//};