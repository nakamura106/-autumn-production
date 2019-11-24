#ifndef DEFINITION_H_
#define DEFINITION_H_

// �\���́Aenum�܂Ƃߗp

#define P_posX			100.0f  //�������W
#define P_posY			600.0f	//�������W
#define P_trp_range		1000.0f	//�U���͈�
#define P_speed			5.0f	//�ړ����x
#define P_jump_power	15.0f	//�W�����v��
#define Gravity			0.5f	//�����p�d��
#define Dispflame		6		//�`�掞��
#define Rect_Height     256.0f	//��`�̍���
#define Rect_Width		256.0f	//��`�̕�
#define RectX			0.25f	//��`�̍�����WX
#define RectY			0.25f	//��`�̍�����WY

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

struct UVANIMATION
{
	int m_Rect_Num;			// ��`�ԍ�
	float m_RectX;			// ��`�̍�����WX
	float m_RectY;			// ��`�̍�����WY
	float m_Rect_Width;		// ��`�̉���
	float m_Rect_Height;		// ��`�̍���
	int m_Display_Flame;		// �\���t���[����
	int Next_Rect_Num;		// ���̋�`�ԍ�
};

#endif
