#pragma once
#include"EnemyBase.h"

class Bird :public EnemyBase {
public:
	Bird();
	~Bird();
	void Init();
	void SetRectangle();

private:
	const std::string	M_AIDataFileName	= "Res/Csv/Bird/Enemy_AI";
	const int			M_SHIT_CYCLE		= 60;
	const int			M_FLYFALL_STOP_ANIMATION = 16;
	const int			M_ATTACK2_ANIM_TEX_NUM = 10;

	int m_savetime_shit_cycle;	//フレーム数格納：フンを落とす周期
	bool m_is_init_motion_end;		//移動状態の際、最初のみ動きを止めるために使用

	/*AI変更関数*/
	EnemyAIType ChangeAIType();

	void InitFlyState();
	void InitAttack1State();

	/*飛行状態前の羽ばたき状態初期化*/
	void InitFlappingState();

	/*EnemyBaseで呼び出す攻撃処理*/
	void EnemyAttack1();
	void EnemyAttack2();
	void EnemyAttack3();
	void EnemyFly();

	void FlyStateRise();	//上昇
	void FlyStateFall();	//下降

	/*EnemyBaseで呼び出す状態初期化処理*/
	void InitAttack3State();//攻撃状態３

	/*フン発射関数*/
	void CreateShitBullet();

	void InitAllState();

};

