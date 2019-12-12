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
	EnemyBase(float speed_, EnemyID enemy_id_);
	virtual ~EnemyBase();

	/*Load用関数？：ObjectBaseから引き継いだ*/
	void Load() {}
	/*描画関数*/
	void Draw();
	/*初期化*/
	virtual void Init();
	/*更新*/
	virtual void Update();


	/*			ゲッター群			*/
	/*状態取得*/
	EnemyStateType	GetEnemyState() { return m_state; }
	
	

private:

	using EnemyAIList = std::vector < EnemyAIParam* >;

	/*初期化用初期値*/
	const int	M_ANIM_FLAME		= 7;		//画像変更を行うフレーム周期
	const int	M_ANIM_TEX_ALL		= 12;		//画像のアニメーション枚数
	const int	M_ANIM_TEX_WIDTH	= 4;		//横の分割数
	const int	M_ANIM_TEX_HEIGHT	= 4;		//縦の分割数
	const float M_ENEMY_SYZE		= 1024.f;	//テクスチャのサイズ(本来は縦横がある)
	const float	M_INIT_POS_X		= 700.f;	//初期x座標
	const float M_INIT_POS_Y		= -70.f;	//初期y座標
	const float M_CURE_SLEEP_TIME_DEFAULT = 30.f;		//ゲージ自動回復のフレーム周期
	const int	M_STOP_AUTO_SLEEP_TIME_DEFAULT = 300;	//ゲージ自動回復を止めるフレーム時間
	const float M_MOVE_LIMIT_X = 2500.f;
	const int	M_GAMECLEAR_FLAME = 180;		//眠りモーション遷移後、ゲームクリア

	/*生成している弾の管理をする関数：Updateで呼び出している*/
	void BulletControl();		

	/*デバッグ用関数：キー入力によってEnemyが変化*/
	void DebugKeyAction();

	/*データバンクへの値渡し*/
	void DataSetUpdate();

	/*当たり時の処理*/
	void HitAction(ObjectRavel ravel_, float hit_use_atk_);

	/*睡眠ゲージの自動回復*/
	void AutoCureSleepGage();

	/*移動範囲制限*/
	bool IsMoveLimitLeft();
	bool IsMoveLimitRight();
	void MoveLimitUpdate();

	/*眠り判定*/
	bool CheckSleepState();

	bool m_stop_state_transition;//CsvAI状態遷移が可能かフラグ：DebugKeyActionで使用

	//状態関係
	EnemyStateType	m_state;					//敵の状態
	int				m_state_saveflame;			//状態継続のフレーム数計測用
	float			m_state_save_pos_x;			//移動距離測定用
	Direction		m_player_pos_relationship;	//プレイヤーとの位置関係
	EnemyAIType		m_now_ai;					//現在使用しているAI
	int				m_now_ai_num;				//現在使用しているAIの進行度
	EnemyAIList		m_ai_list[static_cast<int>(EnemyAIType::EnemyAIType_Max)];	//AIのパターンが格納されたリスト
	bool			m_is_pos_end;				//マップの端まで来た時にtrue 12/10現在使用無し

	EnemyID			m_enemy_id;//敵のID

	//ゲージ関係
	float			m_sleep_gauge;	//眠りゲージ
	float			m_fatigue_gauge;//疲労ゲージ

	float m_auto_sleep_time;	//回復速度
	int m_auto_sleep_saveflame;	//回復時に現在のフレーム数を格納
	int m_stop_auto_sleep_time;	//自動回復を止める時間

	int m_game_clear_saveflame;	//ゲームクリアまでのフレーム数計測用

	//弾関係
	std::vector<EnemyBullet*> bullet_list;//弾のリスト

protected:

	/*			新状態遷移			*/
	/*
		初期化：LoadAIState
	　	毎フレーム：UpdateAIState・AITransitionUpdate
			↓
		遷移確定時：ChangeAIState
			↓
		状態遷移時：ChangeState
		AI変更時：ChangeAIType
	*/

	/*状態更新関数:Csvを使用したAIシステム(以下、CsvAI)。12/10現在はこちらを使用*/
	void UpdateAIState();

	/*csv読込関数：引数にAI番号と.csvを除いたファイル名を入れる*/
	//例：Res/Csv/Mouse/Enemy_AI1.csv→Res/Csv/Mouse/Enemy_AI
	void LoadAIData(std::string file_name_);

	/*AI・状態遷移関数：AI情報を元に状態の遷移かAIの変更を行う*/
	void ChangeAIState();

	/*大元の状態遷移関数：引数で渡した状態に遷移*/
	void ChangeState(EnemyStateType next_state_);
	
	/*CsvAI状態遷移関数：内部でAITransition～関数を呼び出している*/
	void AITransitionUpdate();

	/*CsvAI状態遷移条件管理関数：trueを返すと状態遷移という仕組み*/
	bool AITransitionBase();		//共通する状態遷移条件
	bool AITransitionStraight();	//直線移動によって状態遷移
	bool AITransitionPassPlayer();	//プレイヤーを越えると状態遷移
	bool AITransitionFrontPlayer();	//プレイヤーを前にすると状態遷移
	bool AITransitionDistance();	//指定した距離によって状態遷移
	bool AITransitionFlameTime();	//指定した時間によって状態遷移

	/*CsvAI向き変更関数：状態遷移時、向き変更*/
	void ChangeAIDirection();

	/*AI変更関数：戻り値で戻したAIに変更する*/
	virtual EnemyAIType ChangeAIType() = 0;


	/*			状態更新			*///旧、新状態遷移どちらでも使用

	virtual void EnemyWait();	//待機状態
	virtual void EnemyChase();	//追跡状態
	virtual void EnemyMove();	//移動状態
	virtual void EnemyRefuge();	//逃走状態
	virtual void EnemyAttack1();//攻撃状態１
	virtual void EnemyAttack2();//攻撃状態２
	virtual void EnemyAttack3();//攻撃状態３
	virtual void EnemyRest();	//休憩状態？
	void		 EnemySleep();	//眠り状態


	/*			状態初期化			*/

	virtual void InitAllState() {}	//全状態共通
	virtual void InitWaitState();	//待機状態
	virtual void InitWalkState();	//移動状態
	virtual void InitRefugeState();	//逃走状態
	virtual void InitAttack1State();//攻撃状態１
	virtual void InitAttack2State();//攻撃状態２
	virtual void InitAttack3State();//攻撃状態３
	virtual void InitChaseState();	//追跡状態
	virtual void InitSleepState();	//眠り状態



	/*			旧状態遷移			*/

	/*旧状態更新関数：システムは単純だが、拡張性が無いと判断*/
	void UpdateState();

	/*各状態からの遷移関数*/
	virtual EnemyStateType ChangeStateFromWait();	//待機状態
	virtual EnemyStateType ChangeStateFromWalk();	//移動状態
	virtual EnemyStateType ChangeStateFromRefuge();	//逃走状態
	virtual EnemyStateType ChangeStateFromAttack1();//攻撃状態１
	virtual EnemyStateType ChangeStateFromChase();	//追跡状態

	/*向き変更：m_Directionを変更する LEFT⇔RIGHT*/
	void ChangeDirection();



	/*			ゲージ処理			*/

	/*眠気度の自動回復*/
	virtual void CureSleepiness(float cure_sleep_);
	/*疲労度の自動回復*/
	virtual void CureFatigue(float cure_fatigue_);
	/*眠気度の増加*/
	virtual void DamageSleepness(int damage_sleep_);
	/*疲労度の増加*/
	virtual void DamageFatigue(int damage_fatigue_);


	/*			ゲッター			*/
	/*状態遷移してからの経過時間取得*/
	int	GetStateSaveFlame();
	EnemyAIType GetNowAI() { return m_now_ai; }

	//弾作成
	void CreateBullet(float pos_x_, float pos_y_, float move_speed_);

	/*			全敵共通のパラメータ			*/
	

};


#endif
