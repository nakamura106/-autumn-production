#pragma once
#include"EnemyBase.h"


class Gorilla :public EnemyBase {
public:
	Gorilla();
	~Gorilla();
	void Init();

private:
	const std::string M_AIDataFileName = "Res/Csv/Gorilla/Enemy_AI";

	/*AI変更関数*/
	EnemyAIType ChangeAIType();

	void EnemyAttack1();	//ドラミング
	void EnemyAttack2();	//叩きつけ
	void EnemyAttack3();	//バナナ投げ
	void EnemyFly();		//ジャンプ動作

};
