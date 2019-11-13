#ifndef DEFINITION_H_
#define DEFINITION_H_

// ç\ë¢ëÃÅAenumÇ‹Ç∆Çﬂóp

enum class Player
{
	PlayerTypeTrumpet,
	PlayerTypeFlute,
	PlayerTypeTuba,

	PlayerTypeMax,
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

#endif
