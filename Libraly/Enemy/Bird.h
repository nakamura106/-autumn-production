#pragma once
#include"EnemyBase.h"

class Bird :public EnemyBase {
public:
	Bird();
	~Bird();
	void Init();
	void SetRectangle();

private:
	/*AI変更関数*/
	EnemyAIType ChangeAIType();

	/*EnemyBaseで呼び出す攻撃処理*/
	void EnemyAttack1();
	void EnemyAttack2();
	void EnemyAttack3();

};

