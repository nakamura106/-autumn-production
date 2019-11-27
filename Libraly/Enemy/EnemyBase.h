#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Object/ObjectBase.h"

class EnemyBase :public ObjectBase
{
public:
	EnemyBase();
	~EnemyBase();

	void Create() {}
	void Load(){}

	/*初期化*/
	virtual void Init();
	/*更新*/
	virtual void Update();
	/*描画*/
	void Draw();
	/*アニメーション*/
	void AnimationUpdate();

	/*状態の更新*/
	virtual void UpdateState();
	/*状態の遷移*/
	virtual void ChangeState();

	/*
		状態の処理
	*/
	/*移動*/
	virtual void EnemyMove();
	/*逃走(疲労時)*/
	virtual void EnemyRefuge();
	/*攻撃*/
	virtual void EnemyAttack();
	/*待機*/
	virtual void EnemyIdle();
	/*休憩*/
	virtual void EnemyBreak();

	/*
		ゲッター群
	*/
	/*状態取得*/
	virtual EnemyStateType GetEnemyState();

	/*
		ゲージ処理
	*/
	/*眠気度の自動回復*/
	virtual void CureSleepiness();
	/*疲労度の自動回復*/
	virtual void CureFatigue();
	/*眠気度の増加*/
	virtual void DamageSleepness(int damage_sleep_);
	/*疲労度の増加*/
	virtual void DamageFatigue(int damage_fatigue_);

private:
	/*デバッグ(仮実装)用*/
	int m_anim_timer;				//アニメーション時のフレーム計測用タイマー
	const int M_ANIM_FLAME = 10;		//画像変更を行うフレーム周期
	const int M_ANIM_TEX_ALL = 10;	//画像のアニメーション枚数
	const int M_ANIM_TEX_WIDTH = 5;	//横の分割数
	const int M_ANIM_TEX_HEIGHT = 2;//縦の分割数
	const float M_ENEMY_SYZE = 1024.f;

protected:
	float	m_sleep_gauge;		//眠りゲージ
	float	m_fatigue_gauge;	//疲労ゲージ
	int		m_time_of_break;	//休憩時間
	bool	m_is_break;			//休憩しているか
	bool	m_is_hit_judge;		//当たり判定が存在するか

	EnemyID	m_enemy_id;			//敵のID
	EnemyStateType m_state;		//敵の状態
	EnemyAttackRepertory m_attack_repertory;	//攻撃のバリエーション
	EnemytoPlayerState m_enemy_to_player_state;	//プレイヤーとの関係？

};


#endif
