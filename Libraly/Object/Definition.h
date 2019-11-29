#ifndef DEFINITION_H_
#define DEFINITION_H_

// �\���́Aenum�܂Ƃߗp

#define P_posX			100.0f  //�������W
#define P_posY			600.0f	//�������W
#define P_trp_range		1000.0f	//�U���͈�
#define P_speed			5.0f	//�ړ����x
#define P_jump_power	17.0f	//�W�����v��
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

enum class EnemytoPlayerState
{
	Separated,
	Close,
	Escape,
	Pursue,
	EtoPStateTypeMax,
};

enum class EnemyAttackRepertory
{
	VariableEnumrate_Type,	//�e�G�l�~�[�N���X��typedef���Ďg���N���X
};

enum class EnemyID
{
	Hedgehog,
	Seagull,
	Gorilla,

	BossTypeMax,
};

enum class EnemyStateType 
{
	Wait,	//�ҋ@
	Walk,	//�ړ�
	Attack,	//�U��
	Refuge,	//�s���`��Ԃ̃G�l�~�[����
	//Break�͓����ɉ󂷂Ȃǂ����邽�߁ARest�ɕύX
	//Rest,	//�ҋ@(��J��)
	Chase,	//�ǐ�
	Sleep,	//������
	EnemyStateTypeMax,
};

enum Direction 
{
	 LEFT,
	RIGHT,
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

struct DrawParam
{
	DrawParam() {
		x = 0.0f;
		y = 0.0f;
		tu = 0.0f;
		tv = 0.0f;
		category_id = 0;
		texture_id = 0;
	}
	float x, y, tu, tv;
	int category_id, texture_id;
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
