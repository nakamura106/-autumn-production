#ifndef DEFINITION_H_
#define DEFINITION_H_

// ç\ë¢ëÃÅAenumÇ‹Ç∆Çﬂóp

#define P_posX			100.0f
#define P_posY			600.0f
#define P_trp_range		1000.0f
#define P_speed			5.0f
#define P_jump_power	15.0f
#define Gravity			0.5f

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
