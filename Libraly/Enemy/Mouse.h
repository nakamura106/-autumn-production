#pragma once
#include "EnemyBase.h"


/*
typedef enum AttackRepertoryofHedgeHog
{
	Rush,		//“Ëi
	HeadButt,	//“ª“Ë‚«
	NeedleFire,	//ƒgƒQ”­Ë
	None,		//‰½‚à‚È‚µ
	AttackRepertoryMax,

}EnemyAttackRepertory;
*/

class HedgeHog :public EnemyBase
{
public:
	HedgeHog();
	~HedgeHog();
	
	void Init();
	//void Update();
	

private:
	std::string M_AIDataFileName = "Res/Csv/Mouse/EnemyAI";
	bool m_is_speed_up;		//‰Á‘¬‚·‚é‚©	
	AttackRepertoryofHedgeHog m_attack_repertory;

	/*‘Ò‹@ó‘Ô‚©‚ç‚Ì‘JˆÚ*/
	EnemyStateType ChangeStateFromWait();
	/*ˆÚ“®ó‘Ô‚©‚ç‚Ì‘JˆÚ*/
	EnemyStateType ChangeStateFromWalk();
	/*“¦‘–ó‘Ô‚©‚ç‚Ì‘JˆÚ*/
	EnemyStateType ChangeStateFromRefuge();
	/*UŒ‚ó‘Ô‚©‚ç‚Ì‘JˆÚ*/
	EnemyStateType ChangeStateFromAttack();
	/*’ÇÕó‘Ô‚©‚ç‚Ì‘JˆÚ*/
	EnemyStateType ChangeStateFromChase();

	void EnemyAttack();

	void Headbutt();

	void Rush();

	void NeedleFire();


};