#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Object/ObjectBase.h"
#include"../Engine/FlameTimer.h"
#include"../Bullet/EnemyBullet.h"
#include<vector>
#include<string>

class EnemyBase :public ObjectBase
{
public:
	EnemyBase();
	EnemyBase(float speed_, EnemyID enemy_id_);
	virtual ~EnemyBase();

	void Load(){}
	void Draw();

	/*初期化*/
	virtual void Init();
	/*更新*/
	virtual void Update();

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

	bool m_can_state_transition;

	void BulletControl();

	void DebugKeyAction();

protected:

	/*
		状態の処理
	*/
	
	/*状態の更新*/
	//将来的には廃止　AIのパターン分け仕様に変更
	void UpdateState();

	void UpdateAIState();

	/*AIState遷移*/
	bool TransitionStraight();
	bool TransitionPassPlayer();
	bool TransitionFrontPlayer();
	bool TransitionDistance();
	bool TransitionFlameTime();

	/*待機*/
	virtual void EnemyWait();
	/*追跡*/
	virtual void EnemyChase();
	/*移動*/
	virtual void EnemyMove();
	/*逃走(疲労時)*/
	virtual void EnemyRefuge();
	/*攻撃*/
	virtual void EnemyAttack1();
	virtual void EnemyAttack2();
	virtual void EnemyAttack3();
	/*休憩*/
	virtual void EnemyRest();

	/*
		状態遷移
		デバッグ用として使用
	*/

	/*状態遷移関数②：AI情報を元に遷移*/
	void ChangeAIState();

	/*AI変更関数：戻り値で戻したAIに変更する*/
	virtual EnemyAIType ChangeAIType() = 0;

	/*状態遷移関数①：引数で渡した状態に遷移*/
	void ChangeState(EnemyStateType next_state_);

	/*待機状態からの遷移*/
	virtual EnemyStateType ChangeStateFromWait();
	/*移動状態からの遷移*/
	virtual EnemyStateType ChangeStateFromWalk();
	/*逃走状態からの遷移*/
	virtual EnemyStateType ChangeStateFromRefuge();
	/*攻撃状態からの遷移*/
	virtual EnemyStateType ChangeStateFromAttack1();
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
	virtual void InitAttack1State();
	virtual void InitAttack2State();
	virtual void InitAttack3State();
	
	/*追跡状態*/
	virtual void InitChaseState();
	/*眠り状態(クリア？)*/
	virtual void InitSleepState();

	/*向き変更*/
	void ChangeDirection();

	/*攻撃レパートリーの初期化*/
	//virtual void InitAttackRepertory() = 0;

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

	EnemyID					m_enemy_id;				//敵のID
	EnemyStateType			m_state;				//敵の状態
	int						m_attack_repertory;		//攻撃のバリエーション

	int		m_state_saveflame;	//状態継続のフレーム数計測用

	std::vector<EnemyBullet*> bullet_list;
	std::vector<EnemyAIParam*> m_ai_list[(int)EnemyAIType::EnemyAIType_Max];		//AIのパターンが格納されたリスト
	EnemyAIType m_now_ai;		//現在使用しているAI
	int m_now_ai_num;	//現在使用しているAIの進行度

};


#endif
