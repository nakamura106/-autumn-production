#ifndef DEFINITION_H_
#define DEFINITION_H_

// 構造体、enumまとめ用

#define P_posX 100
#define P_posY 400
#define P_trp_range 1000
#define P_speed 5.0f

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
	ThinkA,
	Think
};

enum class Enemy
{
	BossType01,
	BossType02,
	BossType03,

	BossTypeMax,
};

enum class EnemyStateType 
{
	Idle,
	Warn,
	Attack,
	Refuge,
	Break,
	EnemyStateTypeMax,
};

enum Direction 
{
	 LEFT,
	RIGHT,
};

struct Position
{
	float x;
	float y;
};

#endif
