#ifndef DEFINITION_H_
#define DEFINITION_H_

// 構造体、enumまとめ用

#define P_posX			100.0f  //初期座標
#define P_posYsea		600.0f	//初期座標海
#define P_posYforest	650.0f	//初期座標森
#define P_trp_range		1000.0f	//攻撃範囲
#define P_speed			5.0f	//移動速度
#define P_jump_power	17.0f	//ジャンプ力
#define P_MaxHP			4		//プレイヤーの体力
#define Gravity			0.5f	//落下用重力
#define Dispflame		6		//描画時間
#define Rect_Height     256.0f	//矩形の高さ
#define Rect_Width		256.0f	//矩形の幅
#define RectX			0.25f	//矩形の左上座標X
#define RectY			0.25f	//矩形の左上座標Y
#define MaxRectX		1.0f	//統合画像の端X
#define MaxRectY		0.75f	//統合画像の下端Y
#define MaxAnimationNum	12		//アニメーションの枚数
#define InitRectX		0.0f	//矩形座標初期化用X
#define InitRectY		0.0f	//矩形座標初期化用Y
#define Centerofscreen	700.0f	//プレイヤー停止用画面中央
#define lrAdjustment	130.0f	//左右描画ずれ調整用
#define sel_X			0		//引数X選択
#define sel_Y			1		//引数Y選択
#define sel_XY			2		//引数XY選択
#define A				1		//A
#define B				2		//B
#define floor2speed		3		//

//オブジェクトの役割を示す
enum class ObjectRavel 
{
	Ravel_Player,		//プレイヤー
	Ravel_Boss,			//BOSS(Enemy)
	Ravel_Map,
	Ravel_MapObj,		//マップ上のオブジェクト
	Ravel_PlayerBullet,	//プレイヤーの弾
	Ravel_PlayerBullet2,
	Ravel_PlayerBullet3,
	Ravel_PlayerBullet4,
	Ravel_EnemyBullet,	//エネミーの弾
	ObjectRavel_Max
};

enum class Player
{
	PlayerTypeTrumpet,
	PlayerTypeFlute,
	PlayerTypeTuba,

	PlayerTypeMax,
};

enum class P_State
{
	Wait,
	Move,
	Jump,
	Jump_Attack,
	Jump_Damage,
	Damage,
	Attack,
	ThinkA,
	ThinkB,
	Death,
	Clear,

};

enum class Key
{
	Major,
	Minor,
};

//Bulletの種類
enum class PlayerBulletType {
	Default,
	Chocho_1,
	Chocho_2,
	Tancho_1,
	Tancho_2,
	BulletType_Max
};

//AIの種類
enum class EnemyAIType {
	AI1,
	AI2,
	AI3,
	AI4,
	AI5,
	AI6,
	AI7,
	AI8,
	AI9,
	AI10,
	EnemyAIType_Max
};

//状態持続条件
enum class EnemyTransitionTerm {
	Straight,	//0:直進
	PassPlayer,	//1:プレイヤーとの距離が一致した
	FrontPlayer,//2:プレイヤーを前にした
	Distance,	//3:距離
	FlameTime,	//4:経過フレーム数(時間)
	EnemyTransitionTerm_Max
};

enum class EnemyStateType
{
	Wait,	//0:待機
	Walk,	//1:警戒
	Refuge,	//2:ピンチ状態のエネミー逃走
	Chase,	//3:追跡
	Sleep,	//4:睡眠中
	Attack1,//5:攻撃
	Attack2,//6:攻撃2
	Attack3,//7:攻撃3
	EnemyStateTypeMax,
};

//Enemyのcsvからの値を判定するため
enum class EnemyDirection {
	Right,	//0:右方向
	Left,	//1:左方向
	Reverse,//2:逆方向
	Same,	//3:同じ方向
	EnemyDirection_Max
};


//AIのパラメータ
struct EnemyAIParam {
	EnemyAIParam() {
		e_state = EnemyStateType::Wait;
		e_speed_default = 0;
		e_speed_sleep = 0;
		e_speed_tired = 0;
		e_transition_term = EnemyTransitionTerm::FlameTime;
		e_transition_num = 0;
		e_direction = EnemyDirection::Same;
	}

	EnemyStateType		e_state;			//遷移する状態
	int					e_speed_default;	//通常のスピード
	int					e_speed_sleep;		//眠気時のスピード
	int					e_speed_tired;		//疲労時のスピード
	EnemyTransitionTerm e_transition_term;	//状態持続条件
	int					e_transition_num;	//状態持続条件に対応する値
	EnemyDirection		e_direction;		//向き
};

//CsvでのAIのパラメータの配列番号
enum class EnemyAIArrayNum {
	OrderNum,
	State,
	Speed_Default,
	Speed_Sleep,
	Speed_Tired,
	Transition_Term,
	Transition_Num,
	Enemy_Direction,
	EnemyAIArrayNum_Max
};

enum class EnemyAttackRepertory
{
	VariableEnumrate_Type,	//各エネミークラスでtypedefして使うクラス
};

enum class EnemyID
{
	Hedgehog,
	Seagull,
	Gorilla,

	BossTypeMax,
};

enum class MapObjId
{
	bg,
	floor1,
	floor2,
	fg,
	obj1,
	obj2,
	obj3,
	MaxObj,
};

enum class Mapvar
{
	X,
	Y,
	speed,
	Maxvar,
};

enum Direction 
{
	LEFT,
	RIGHT,
};

// プレイヤーのHp状態　UIで使用
enum class PlayerHpState
{
	Hp4,
	Hp3,	// 残りHP３の状態
	Hp2,
	Hp1,
	Hp0,
};

struct Position
{
	Position() {
		x = 0.0f;
		y = 0.0f;
	}

	float x;
	float y;
};

// 描画用変数の構造体
struct DrawParam
{
	DrawParam() {
		tu = 0.0f;
		tv = 0.0f;
		tex_size_x = 0.0f;
		tex_size_y = 0.0f;
		category_id = 0;
		texture_id = 0;
	}
	float tu;
	float tv; 
	float tex_size_x;//テクスチャの横サイズ
	float tex_size_y;//テクスチャの縦サイズ

	// GetTexture()の中身で使う
	int category_id;	
	int texture_id;		
};

// 当たり判定用構造体
struct HitRectangle
{
	float shift_x, shift_y;	// 座標調整変数
	float width, height;	// 当たり判定用矩形の幅、高さ
};

//UVアニメーション用構造体(ObjectBaseで使用)
struct AnimationParam 
{
	AnimationParam() {
		split_width = 1;
		split_height = 1;
		split_all = 1;
		change_flame = 1;
	}

	int split_width;	//横分割数
	int split_height;	//縦分割数
	int split_all;		//合計分割数(縦×横-不要部分)
	int change_flame;	//画像変更のタイミング(フレーム数)

	/*Note:「split」は割れ目・分裂の意味*/
	
};

struct UVANIMATION
{
				
	float m_RectX;			// 矩形の左上座標X
	float m_RectY;			// 矩形の左上座標Y
	float m_Rect_Width;		// 矩形の横幅
	float m_Rect_Height;	// 矩形の高さ
	int m_Display_Flame;	// 表示フレーム数
		
};

struct EffectInfo
{
	float m_x;			//エフェクトのx座標
	float m_y;			//エフェクトのy座標
	int m_timer;		//描画時間タイマー
	int m_tex_id;		//テクスチャーid保存用
	bool m_is_active;	//描画判断用
	float m_width;		//横幅
	float m_height;		//高さ
	float m_tu;
	float m_tv;
};


#endif
