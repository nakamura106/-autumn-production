#pragma once


#include"../Object/ObjectBase.h"

class EnemyBase :public ObjectBase
{
public:
	EnemyBase();
	~EnemyBase();

	virtual void Init()=0;
	virtual void Create()=0;
	virtual void Update()=0;
	virtual void Draw()=0;

	virtual int GetEnemyPosX();
	virtual int GetEnemyPosY();

	virtual void UpdateState();
	virtual void ChangeState();

	virtual void EnemyMove();
	virtual void EnemyRefuge();
	virtual void EnemyAttack();
	virtual void EnemyIdle();
	virtual void EnemyBreak();

protected:

	float m_sleep_gauge;	//ñ∞ÇËÉQÅ[ÉW
	float m_fatigue_gauge;	//îÊòJÉQÅ[ÉW
	
	Enemy m_Enemy_Id;
	EnemyStateType m_State;

};
