#ifndef DEFINITION_H_
#define DEFINITION_H_

// �\���́Aenum�܂Ƃߗp

#define P_posX			100.0f  //�������W
#define P_posY			600.0f	//�������W
#define P_trp_range		1000.0f	//�U���͈�
#define P_speed			5.0f	//�ړ����x
#define P_jump_power	17.0f	//�W�����v��
#define P_MaxHP			5		//�v���C���[�̗̑�
#define Gravity			0.5f	//�����p�d��
#define Dispflame		6		//�`�掞��
#define Rect_Height     256.0f	//��`�̍���
#define Rect_Width		256.0f	//��`�̕�
#define RectX			0.25f	//��`�̍�����WX
#define RectY			0.25f	//��`�̍�����WY
#define MaxRectX		1.0f	//�����摜�̒[X
#define MaxRectY		0.75f	//�����摜�̉��[Y
#define MaxAnimationNum	12		//�A�j���[�V�����̖���
#define InitRectX		0.0f	//��`���W�������pX
#define InitRectY		0.0f	//��`���W�������pY
#define Centerofscreen	704.0f	//�v���C���[��~�p��ʒ���
#define lrAdjustment	128.0f	//���E�`�悸�꒲���p
#define sel_X			0		//����X�I��
#define sel_Y			1		//����Y�I��
#define sel_XY			2		//����XY�I��
#define A				1		//A
#define B				2		//B


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

//�G���猩��v���C���[�̓���
enum class EnemytoPlayerState
{
	Separated,	//���ꂽ
	Close,		//�߂�
	Escape,		//������
	Pursue,		//�ǂ�
	EtoPStateTypeMax,
};

//��Ԏ�������
enum class EnemyTransitionTerm {
	Straight,	//���i
	PassPlayer,	//�v���C���[�Ƃ̋�������v����
	FrontPlayer,//�v���C���[��O�ɂ���
	Distance,	//����
	FlameTime,	//�o�߃t���[����(����)
	EnemyTransitionTerm_Max
};

//AI�̎��
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

enum class EnemyStateType
{
	Wait,	//�ҋ@
	Walk,	//�x��
	Refuge,	//�s���`��Ԃ̃G�l�~�[����
	Chase,	//�ǐ�
	Sleep,	//������
	Attack1,//�U��
	Attack2,//�U��2
	Attack3,//�U��3
	EnemyStateTypeMax,
};


//AI�̃p�����[�^
struct EnemyAIParam {
	EnemyStateType		e_state;			//�J�ڂ�����
	float				e_speed_default;	//�ʏ�̃X�s�[�h
	float				e_speed_sleep;		//���C���̃X�s�[�h
	float				e_speed_tired;		//��J���̃X�s�[�h
	EnemyTransitionTerm e_transition_term;	//��Ԏ�������
	int					e_transition_num;	//��Ԏ��������ɑΉ�����l
};

//Csv�ł�AI�̃p�����[�^�̔z��ԍ�
enum class EnemyAIArrayNum {
	OrderNum,
	State,
	Speed_Default,
	Speed_Sleep,
	Speed_Tired,
	Transition_Term,
	Transition_Num,
	EnemyAIArrayNum_Max
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

enum Direction 
{
	LEFT,
	RIGHT,
};

// �v���C���[��Hp��ԁ@UI�Ŏg�p
enum PlayerHpState
{
	Hp3,	// �c��HP�R�̏��
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

// �`��p�ϐ��̍\����
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
	float tex_size_x;//�e�N�X�`���̉��T�C�Y
	float tex_size_y;//�e�N�X�`���̏c�T�C�Y

	// GetTexture()�̒��g�Ŏg��
	int category_id;	
	int texture_id;		
};

// �����蔻��p�\����
struct Rectangle
{
	
};

//UV�A�j���[�V�����p�\����(ObjectBase�Ŏg�p)
struct AnimationParam 
{
	AnimationParam() {
		split_width = 1;
		split_height = 1;
		split_all = 1;
		change_flame = 1;
	}

	int split_width;	//��������
	int split_height;	//�c������
	int split_all;		//���v������(�c�~��-�s�v����)
	int change_flame;	//�摜�ύX�̃^�C�~���O(�t���[����)

	/*Note:�usplit�v�͊���ځE����̈Ӗ�*/
	
};

struct UVANIMATION
{
				
	float m_RectX;			// ��`�̍�����WX
	float m_RectY;			// ��`�̍�����WY
	float m_Rect_Width;		// ��`�̉���
	float m_Rect_Height;	// ��`�̍���
	int m_Display_Flame;	// �\���t���[����
		
};

struct EffectInfo
{
	float m_x;			//�G�t�F�N�g��x���W
	float m_y;			//�G�t�F�N�g��y���W
	int m_timer;		//�`�掞�ԃ^�C�}�[
	int m_tex_id;		//�e�N�X�`���[id�ۑ��p
	bool m_is_active;	//�`�攻�f�p
	float m_width;		//����
	float m_height;		//����
	float m_tu;
	float m_tv;
};


#endif
