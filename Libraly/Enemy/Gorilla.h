#pragma once
#include"EnemyBase.h"


class Gorilla :public EnemyBase {
public:
	Gorilla();
	~Gorilla();
	void Init();

private:
	const std::string M_AIDataFileName = "Res/Csv/Gorilla/Enemy_AI";
	const float		  M_JUMP_ACCELERATION_DEFAULT = 0.4f;
	const int		M_JUMP_STOP_ANIM_FLAME = 4;
	const float		  M_JUMP_SPEED_DEFAULT = 15.f;

	float m_jump_acceleration;	//ジャンプ時のy軸加速度
	bool  m_do_doraming;		//ドラミング中かどうか
	float m_jump_speed;			//ジャンプ中のy軸移動量
	bool  m_end_jump;			//ジャンプが終わったかどうか1/18雑コード

	/*AI変更関数*/
	EnemyAIType ChangeAIType();

	void EnemyAttack1();	//ドラミング
	void EnemyAttack2();	//叩きつけ
	void EnemyAttack3();	//バナナ投げ
	void EnemyAttack4();	//サル召喚
	void EnemyFly();		//ジャンプ動作

	void InitAllState();	//全状態共通
	void InitSleepState();
	void InitFlyState();

	void CreateBanana();
	void CreateMonkey();

};
