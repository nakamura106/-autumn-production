#pragma once
#include"EnemyBase.h"


class Gorilla :public EnemyBase {
public:
	Gorilla();
	~Gorilla();
	void Init();

private:
	const std::string M_AIDataFileName = "Res/Csv/Gorilla/Enemy_AI";

	/*AI�ύX�֐�*/
	EnemyAIType ChangeAIType();

	void EnemyAttack1();	//�h���~���O
	void EnemyAttack2();	//�@����
	void EnemyAttack3();	//�o�i�i����
	void EnemyFly();		//�W�����v����

};
