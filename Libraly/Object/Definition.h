#ifndef DEFINITION_H_
#define DEFINITION_H_

// �\���́Aenum�܂Ƃߗp

#define P_posX			100.0f  //�������W
#define P_posYsea		600.0f	//�������W�C
#define P_posYforest	650.0f	//�������W�X
#define P_trp_range		1000.0f	//�U���͈�
#define P_speed			5.0f	//�ړ����xf
#define P_jump_power	17.0f	//�W�����v��
#define P_MaxHP			4		//�v���C���[�̗̑�
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
#define Centerofscreen	700.0f	//�v���C���[��~�p��ʒ���
#define lrAdjustment	130.0f	//���E�`�悸�꒲���p
#define sel_X			0		//����X�I��
#define sel_Y			1		//����Y�I��
#define sel_XY			2		//����XY�I��
#define A				1		//A
#define B				2		//B
#define floor2speed		3		//

/*�G�̃p�����[�^*/
#define Num_of_TakeaBreak  100		//�x�e���Ƃ�i��J�x�́j���l
#define Refuge_Time	100				//������鎞��
#define Limit_of_BreakTime 100		//MAX�̋x�e����
#define Cure_of_SleepinessPoint 0.5f	//���ԉ񕜂��閰�C�̒l
#define Cure_of_FatiguePoint 1		//���ԉ񕜂����J�̒l
#define Distance_of_Maintain 100	//�ێ�����K�؂ȋ���

#define Fatigue_Gauge_Max 100		//��J�Q�[�W���
#define Sleep_Gauge_Max	75			//�����Q�[�W���

#define Attack_Interval 100			//�U�����o

const int GAMECLEAR_FLAME = 180;	//�G�̖��胂�[�V�����J�ڌ�A���̃t���[�����o�߂ŃQ�[���N���A
const int GAMEOVER_FLAME = 180;		//�G�̎��S���[�V�����J�ڌ�A���̃t���[�����o�߂ŃQ�[���I�[�o�[
const float G_GROUND_POS_Y = 950.f;//�n�ʂ̈ʒu

//�I�u�W�F�N�g�̖���������
enum class ObjectRavel 
{
	Ravel_Player,		//�v���C���[
	Ravel_Boss,			//BOSS(Enemy)
	Ravel_Map,
	Ravel_MapObj,		//�}�b�v��̃I�u�W�F�N�g
	Ravel_PlayerBullet,	//�v���C���[�̒e
	Ravel_PlayerBullet2,
	Ravel_PlayerBullet3,
	Ravel_PlayerBullet4,
	Ravel_EnemyBullet,	//�G�l�~�[�̒e
	ObjectRavel_Max
};

enum class Player
{
	PlayerTypeTrumpet,
	PlayerTypeFlute,
	PlayerTypeTuba,

	PlayerTypeMax,
};

enum class MapType
{
	WoodsMap,
	SeaMap,
	CityMap,

	MapTypeMax,
};

enum class P_effect
{
	None,
	Debuff,
	Failure,
	Hit,
	Landing,
	Shot,
	Sweat,
	MaxEffect
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
	Miss,
	Landing,
	Death,
	Clear,

};

enum class Key
{
	Major,
	Minor,
};

//Bullet�̎��
enum class PlayerBulletType {
	Default,
	Chocho_1,
	Chocho_2,
	Tancho_1,
	Tancho_2,
	BulletType_Max
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

//��Ԏ�������
enum class EnemyTransitionTerm {
	Straight,	//0:���i
	PassPlayer,	//1:�v���C���[�Ƃ̋�������v����
	FrontPlayer,//2:�v���C���[��O�ɂ���
	Distance,	//3:����
	FlameTime,	//4:�o�߃t���[����(����)
	EnemyTransitionTerm_Max
};

enum class EnemyStateType
{
	Wait,	//0:�ҋ@
	Walk,	//1:�x��
	Refuge,	//2:�s���`��Ԃ̃G�l�~�[����
	Chase,	//3:�ǐ�
	Sleep,	//4:������
	Attack1,//5:�U��
	Attack2,//6:�U��2
	Attack3,//7:�U��3
	Dead,	//8:���S
	Fly,	//9:��s
	Attack4,//10:�U��4
	EnemyStateType_Max,
};

//Enemy��csv����̒l�𔻒肷�邽��
enum class EnemyDirection {
	Right,	//0:�E����
	Left,	//1:������
	Reverse,//2:�t����
	Same,	//3:��������
	EnemyDirection_Max
};

// �����蔻��p�̌`�̎��
enum class ShapeType {
	Shape_Circle,	// �~
	Shape_Rect,		// ��`
	Shape_Line,		// ��

	ShapeTypeMax,
	ShapeTypeNon = ShapeTypeMax,
};

enum class WaveType {
	Wave1,
	Wave2,
	Wave3,
	WaveMax,
};


//AI�̃p�����[�^
struct EnemyAIParam {
	EnemyAIParam() {
		e_state = EnemyStateType::Wait;
		e_speed_default = 0;
		e_speed_sleep = 0;
		e_speed_fatigue = 0;
		e_transition_term = EnemyTransitionTerm::FlameTime;
		e_transition_num = 0;
		e_direction = EnemyDirection::Same;
	}

	EnemyStateType		e_state;			//�J�ڂ�����
	int					e_speed_default;	//�ʏ�̃X�s�[�h
	int					e_speed_sleep;		//���C���̃X�s�[�h
	int					e_speed_fatigue;		//��J���̃X�s�[�h
	EnemyTransitionTerm e_transition_term;	//��Ԏ�������
	int					e_transition_num;	//��Ԏ��������ɑΉ�����l
	EnemyDirection		e_direction;		//����
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
	Enemy_Direction,
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

//�G�̃Q�[�W�����ɂ�����Ԃ�����
enum class GageState {
	Normal_State,
	Fatigue_State,
	Sleep_State,
	GageState_Max
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

// �v���C���[��Hp��ԁ@UI�Ŏg�p
enum class PlayerHpState
{
	Hp4,
	Hp3,	// �c��HP�R�̏��
	Hp2,
	Hp1,
	Hp0,
};

// �G�t�F�N�g�̎�ޔ���p
enum class EffectID 
{
	DebuffEffect,
	DieEffect,
	FailureEffect,
	HitEffect,
	LandingEffect,
	ShotEffect,
	SleepEffect,
	SweatEffect,

	MAXEffectID,
};

struct Position
{
	//������Z�q�̃I�[�o�[���[�h
	Position &operator =(const Position &position_) {
		this->x = position_.x;
		this->y = position_.y;
		return *this;
	}

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
struct HitRectangle
{
	float shift_x, shift_y;	// ���W�����ϐ�
	float width, height;	// �����蔻��p��`�̕��A����
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

//Wave�ύX�����̈ڂ�ς��
enum class WaveState {
	None,			//�J�ڂȂ�
	Change_Start,	//�J�ڊJ�n���G�s���J�n
	EnemyMoved,		//�G�s���I�����A�C�e���𗎂Ƃ�
	ItemGet,		//�A�C�e�����聨�G���[�V����
	EnemyNewMotion,	//�G�̐V�������[�V�����J�n���I��
	Change_End,		//�J�ڏI��
};


#endif
