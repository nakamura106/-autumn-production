#ifndef DEFINITION_H_
#define DEFINITION_H_

// 構造体、enumまとめ用

enum class Player
{
	PlayerTypeTrumpet,
	PlayerTypeFlute,
	PlayerTypeTuba,

	PlayerTypeMax,
};

enum class PlayerState
{
	Wait,
	Move,
	Jump,
	ThinkA,
	ThinkB
};

enum class Enemy
{
	BossType01,
	BossType02,
	BossType03,

	BossTypeMax,
};

struct Position
{
	float x;
	float y;
};

enum EnemyStateType
{
	MinStateType,	//リスト最小数
	Idle,			//待機
	Break,			//疲労状態の待機
	Warn,			//警戒
	Attack,			//攻撃
	Refuge,			//逃走
	MaxStateType	//リスト最大数
};

#endif
