#ifndef MOUSE_H_
#define MOUSE_H_

#include "EnemyBase.h"

//!~

typedef enum AttackRepertoryofHedgeHog
{
	Rush,
	HeadButt,
	NeedleFire,
	None,
	AttackRepertoryMax,
}EnemyAttackRepertory;

//~!

class Hedgehog :public EnemyBase 
{
public:
	Hedgehog();
	~Hedgehog();

	virtual void Init() = 0;
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void ChangeState();

	virtual void EnemyMove();
	virtual void EnemyRefuge();
	virtual void EnemyAttack();
	virtual void EnemyIdle();
	virtual void EnemyBreak();

};

#endif
