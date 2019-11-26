#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Object/ObjectBase.h"

class EnemyBase :public ObjectBase
{
public:
	EnemyBase();
	~EnemyBase();

	/*‰Šú‰»*/
	virtual void Init();
	/*XV*/
	virtual void Update();
	/*•`‰æ*/
	virtual void Draw();

	/*ó‘Ô‚ÌXV*/
	virtual void UpdateState();
	/*ó‘Ô‚Ì‘JˆÚ*/
	virtual void ChangeState();

	/*
		ó‘Ô‚Ìˆ—
	*/
	/*ˆÚ“®*/
	virtual void EnemyMove();
	/*“¦‘–(”æ˜J)*/
	virtual void EnemyRefuge();
	/*UŒ‚*/
	virtual void EnemyAttack();
	/*‘Ò‹@*/
	virtual void EnemyIdle();
	/*‹xŒe*/
	virtual void EnemyBreak();

	/*
		ƒQƒbƒ^[ŒQ
	*/
	/*ó‘Ôæ“¾*/
	virtual EnemyStateType GetEnemyState();

	/*
		ƒQ[ƒWˆ—
	*/
	/*–°‹C“x‚Ì©“®‰ñ•œ*/
	virtual void CureSleepiness();
	/*”æ˜J“x‚Ì©“®‰ñ•œ*/
	virtual void CureFatigue();
	/*–°‹C“x‚Ì‘‰Á*/
	virtual void DamageSleepness(int damage_sleep_);
	/*”æ˜J“x‚Ì‘‰Á*/
	virtual void DamageFatigue(int damage_fatigue_);

protected:

	float	m_sleep_gauge;		//–°‚èƒQ[ƒW
	float	m_fatigue_gauge;	//”æ˜JƒQ[ƒW
	int		m_time_of_break;	//‹xŒeŠÔ
	bool	m_is_break;			//‹xŒe‚µ‚Ä‚¢‚é‚©
	bool	m_is_hit_judge;		//“–‚½‚è”»’è‚ª‘¶İ‚·‚é‚©

	Enemy	m_Enemy_Id;			//“G‚ÌID
	EnemyStateType m_State;		//“G‚Ìó‘Ô
	EnemyAttackRepertory m_attack_repertory;	//UŒ‚‚ÌƒoƒŠƒG[ƒVƒ‡ƒ“
	EnemytoPlayerState m_enemy_to_player_state;	//ƒvƒŒƒCƒ„[‚Æ‚ÌŠÖŒWH

};


#endif
