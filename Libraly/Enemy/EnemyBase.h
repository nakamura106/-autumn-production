#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Object/ObjectBase.h"

class EnemyBase :public ObjectBase
{
public:

	virtual void Init() = 0;
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual int GetEnemyPosX();
	virtual int GetEnemyPosY();
	virtual EnemyStateType GetEnemyState();

	virtual void UpdateState();
	virtual void ChangeState();

	virtual void EnemyMove();
	virtual void EnemyRefuge();
	virtual void EnemyAttack();
	virtual void EnemyIdle();
	virtual void EnemyBreak();

	virtual int GetSleepGauge();
	virtual int GetFatigueGauge();

	virtual void CureSleepiness();
	virtual void CureFatigue();

	virtual void DamageSleepness(int damage_sleep_);
	virtual void DamageFatigue(int damage_fatigue_);

protected:

	float m_sleep_gauge;	//–°‚èƒQ[ƒW
	float m_fatigue_gauge;	//”æ˜JƒQ[ƒW
	int m_time_of_break;	//‹xŒeŠÔ
	bool m_is_break;		//‹xŒe‚µ‚Ä‚¢‚é‚©
	bool m_is_hit_judge;	//“–‚½‚è”»’è‚ª‘¶İ‚·‚é‚©
	float m_speed;			//ƒXƒs[ƒh

	Position m_enemy_pos;
	Enemy m_Enemy_Id;
	EnemyStateType m_State;
	EnemyAttackRepertory m_attack_repertory;
	EnemytoPlayerState m_enemy_to_player_state;

public:
	EnemyBase();
	~EnemyBase();

};


#endif
