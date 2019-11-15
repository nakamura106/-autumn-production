#include "Object/ObjectBase.h"
#include "Object/Definition.h"

#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

class EnemyBase:public ObjectBase  
{
public:

	virtual int GetEnemyPosX();
	virtual int GetEnemyPosY();

	virtual void UpdateState();
	virtual void ChangeState();

	virtual void EnemyMove();
	virtual void EnemyRefuge();
	virtual void EnemyAttack();
	virtual void EnemyIdle();
	virtual void EnemyBreak();
//	virtual void EnemyRefuge();
//	virtual void EnemyWarn();



protected:

	Enemy m_Enemy_Id;
	EnemyStateType m_State;
	int m_Palam_Sleepiness;
	int m_Param_Fatigue;

public:

	EnemyBase();
	~EnemyBase();

};

#endif