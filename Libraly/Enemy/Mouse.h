#pragma once
#include "EnemyBase.h"




class HedgeHog :public EnemyBase
{
public:
	HedgeHog();
	~HedgeHog();
	
	void Init();

	void SetRectangle()override;

private:
	

	//ハリ発射位置調整用
	//note:Adjustは「調整」という意味
	const float M_NEEDLE_ADJUST_X = 90.f;
	const float M_NEEDLE_ADJUST_Y = 310.f;

	const float M_DASHATTACK_SPEED_CHANGE_NUM = 1.02f;

	//攻撃時動作のタイミング定数
	const int	M_ATTACK1_ANIM_TEX_NUM = 9;
	const int	M_ATTACK2_ANIM_TEX_NUM = 7;
	const int	M_ATTACK3_ANIM_TEX_NUM = 5;

	
	const std::string M_AIDataFileName = "Res/Csv/Mouse/Enemy_AI";
	bool m_is_speed_up;		//加速するか	
	//AttackRepertoryHedgeHog m_attack_repertory;

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
	//void InitAttackRepertory();

	/*EnemyBaseで呼び出す攻撃処理*/
	void EnemyAttack1();
	void EnemyAttack2();
	void EnemyAttack3();

	void InitAllState();

	//bool m_is_speed_up;		//加速するか
	
};