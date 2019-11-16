#ifndef DEFINITION_H_
#define DEFINITION_H_

// �\���́Aenum�܂Ƃߗp

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
	MinStateType,	//���X�g�ŏ���
	Idle,			//�ҋ@
	Break,			//��J��Ԃ̑ҋ@
	Warn,			//�x��
	Attack,			//�U��
	Refuge,			//����
	MaxStateType	//���X�g�ő吔
};

#endif
