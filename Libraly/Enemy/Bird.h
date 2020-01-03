#pragma once
#include"EnemyBase.h"

class Bird :public EnemyBase {
public:
	Bird();
	~Bird();
	void Init();
	void SetRectangle();

private:
	const std::string M_AIDataFileName = "Res/Csv/Bird/Enemy_AI";

	/*AI変更関数*/
	EnemyAIType ChangeAIType();

	/*EnemyBaseで呼び出す攻撃処理*/
	void EnemyAttack1();
	void EnemyAttack2();
	void EnemyAttack3();

	/*EnemyBaseで呼び出す状態初期化処理*/
	void InitAttack3State();//攻撃状態３

};

