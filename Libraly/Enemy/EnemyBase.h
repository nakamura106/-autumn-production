#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Object/ObjectBase.h"
#include"../Engine/FlameTimer.h"
#include<vector>
#include<string>

//AIリストの大きさ
const int G_ENEMY_AILIST_MAX = 10;

class EnemyBase :public ObjectBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	void Load(){}

	/*初期化*/
	virtual void Init();
	/*更新*/
	virtual void Update();

	/*状態の更新*/
	void UpdateState();

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
	/*攻撃後の処理*/
	virtual void BackBeforeAttackState();

private:
	/*初期化用初期値*/
	const int	M_ANIM_FLAME		= 7;		//画像変更を行うフレーム周期
	const int	M_ANIM_TEX_ALL		= 12;		//画像のアニメーション枚数
	const int	M_ANIM_TEX_WIDTH	= 4;		//横の分割数
	const int	M_ANIM_TEX_HEIGHT	= 4;		//縦の分割数
	const float M_ENEMY_SYZE		= 1024.f;	//テクスチャのサイズ(本来は縦横がある)
	const float	M_INIT_POS_X		= 700.f;	//初期x座標
	const float M_INIT_POS_Y		= -100.f;	//初期y座標

protected:

	/*
		状態の処理
	*/
	/*待機*/
	virtual void EnemyWait();
	/*追跡*/
	virtual void EnemyChase();
	/*移動*/
	virtual void EnemyMove();
	/*逃走(疲労時)*/
	virtual void EnemyRefuge();
	/*攻撃*/
	virtual void EnemyAttack();
	/*休憩*/
	virtual void EnemyRest();

	/*
		状態遷移
		デバッグ用として使用
	*/
	virtual void ChangeState();
	void ChangeState(EnemyStateType next_state_);

	/*待機状態からの遷移*/
	virtual EnemyStateType ChangeStateFromWait();
	/*移動状態からの遷移*/
	virtual EnemyStateType ChangeStateFromWalk();
	/*逃走状態からの遷移*/
	virtual EnemyStateType ChangeStateFromRefuge();
	/*攻撃状態からの遷移*/
	virtual EnemyStateType ChangeStateFromAttack();
	/*追跡状態からの遷移*/
	virtual EnemyStateType ChangeStateFromChase();

	
	/*
		状態初期化
	*/
	/*待機状態*/
	virtual void InitWaitState();
	/*移動状態*/
	virtual void InitWalkState();
	/*逃走状態*/
	virtual void InitRefugeState();
	/*攻撃状態*/
	virtual void InitAttackState();
	/*追跡状態*/
	virtual void InitChaseState();
	/*眠り状態(クリア？)*/
	virtual void InitSleepState();

	/*向き変更*/
	void ChangeDirection();

	/*csvファイル読み込み*/
	//引数にAIの番号と.csvを除いた
	//ファイル名を入れる
	//例：Res/Csv/EnemyAI1.csv→Res/Csv/EnemyAI
	void LoadAIData(std::string file_name_);

	float	m_sleep_gauge;		//眠りゲージ
	float	m_fatigue_gauge;	//疲労ゲージ
	int		m_time_of_break;	//休憩時間
	bool	m_is_break;			//休憩しているか
	bool	m_is_hit_judge;		//当たり判定が存在するか
	int		m_refuge_time;		//逃げ回る時間
	int		m_atk_time_count;	//攻撃間隔カウンター
	float	m_speed;			//スピード

	EnemyID					m_enemy_id;				//敵のID
	EnemyStateType			m_state;				//敵の状態
	EnemyAttackRepertory	m_attack_repertory;		//攻撃のバリエーション
	EnemytoPlayerState		m_enemy_to_player_state;//プレイヤーとの関係？

	int		m_state_saveflame;	//状態継続のフレーム数計測用
	std::vector<EnemyAIParam*> m_ai_list[G_ENEMY_AILIST_MAX];		//AIのパターンが格納されたリスト

};


#endif
