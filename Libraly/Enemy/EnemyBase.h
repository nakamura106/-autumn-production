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

	float m_sleep_gauge;	//����Q�[�W
	float m_fatigue_gauge;	//��J�Q�[�W
	int m_time_of_break;	//�x�e����
	bool m_is_break;		//�x�e���Ă��邩
	bool m_is_hit_judge;	//�����蔻�肪���݂��邩
	float m_speed;			//�X�s�[�h

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
