#pragma once
#include "EnemyBase.h"




class HedgeHog :public EnemyBase
{
public:
	HedgeHog();
	~HedgeHog();
	
	void Init();
	//void Update();

	void SetRectangle()override;
	

private:
	//ハリネズミの攻撃レパートリー
	enum class AttackRepertoryHedgeHog
	{
		Rush,		//突進
		HeadButt,	//頭突き
		NeedleFire,	//トゲ発射
		AttackRepertoryMax
	};

	//ハリ発射位置調整用
	//note:Adjustは「調整」という意味
	const float M_NEEDLE_ADJUST_X = 180.f;
	const float M_NEEDLE_ADJUST_Y = 630.f;
	
	std::string M_AIDataFileName = "Res/Csv/Mouse/EnemyAI";
	bool m_is_speed_up;		//加速するか	
	AttackRepertoryHedgeHog m_attack_repertory;

	/*待機状態からの遷移*/
	EnemyStateType ChangeStateFromWait();
	/*移動状態からの遷移*/
	EnemyStateType ChangeStateFromWalk();
	/*逃走状態からの遷移*/
	EnemyStateType ChangeStateFromRefuge();
	/*攻撃状態からの遷移*/
	EnemyStateType ChangeStateFromAttack1();
	/*追跡状態からの遷移*/
	EnemyStateType ChangeStateFromChase();

	/*AI変更関数*/
	EnemyAIType ChangeAIType();

	/*攻撃レパートリーの初期化*/
	void InitAttackRepertory();

	/*EnemyBaseで呼び出す攻撃処理*/
	void EnemyAttack1();
	void EnemyAttack2();
	void EnemyAttack3();
	
	/*ハリ発射*/
	void CreateNeedle();

	//bool m_is_speed_up;		//加速するか
	bool m_do_needle;		//ハリ発射を行ったかどうか
};