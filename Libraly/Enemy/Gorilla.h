#pragma once
#include"EnemyBase.h"


class Gorilla :public EnemyBase {
public:
	Gorilla();
	~Gorilla();
	void Init();

private:
	const std::string	M_AIDataFileName			= "Res/Csv/Gorilla/Enemy_AI";
	const float			M_JUMP_ACCELERATION_DEFAULT	= 0.4f;
	const int			M_JUMP_STOP_ANIM_FLAME		= 7;
	const float			M_JUMP_SPEED_DEFAULT		= 20.f;
	const float			M_SHOT_ADJUST_X_INPACT		= 220.f;
	const int			M_ATTACK2_ANIM_TEX_NUM		= 13;
	const float			M_INPACT_RIGHT_B_ADJUST		= 270.f;
	const float			M_INPACT_LEFT_B_ADJUST		= -300.f;
	const float			M_INPACT_B_ADJUST_Y			= -100.f;
	const float			M_INPACT_ACTIVE_DISTANCE	= 600.f;
	const float			M_GORILLA_TEX_SIZE			= 850.f;
	const float			M_POS_Y_ADJUST				= -150.f;
	const int			M_FRAME_BANANA_START		= 13;
	const float			M_TEX_FRONT_SPACE = 250.f;

	const EnemyAIType	M_DEADLY_AI = EnemyAIType::AI10;	//�K�E�Z��AI�^�C�v

	//�o�i�i���ˎ��̎�̈ʒu
	const float			M_BANANA_HAND_POS_X[16] = {
							357.f,208.f,209.f,227.f,
							233.f,295.f,385.f,459.f,
							513.f,511.f,465.f,199.f,
							261.f,387.f,0.f,0.f };
	const float			M_BANANA_HAND_POS_Y[16] = {
							801.f,625.f,393.f,409.f,
							487.f,606.f,687.f,691.f,
							681.f,669.f,629.f,449.f,
							291.f,247.f,0.f,0.f };


	float m_jump_acceleration;	//�W�����v����y�������x
	bool  m_do_doraming;		//�h���~���O�����ǂ���
	float m_jump_speed;			//�W�����v����y���ړ���
	bool  m_end_jump;			//�W�����v���I��������ǂ���1/18�G�R�[�h
	Position m_shot_adjust_default;	//�e�̔��ˈʒu����y�����̕W���l

	/*AI�ύX�֐�*/
	EnemyAIType ChangeAIType();

	void EnemyAttack1();	//�h���~���O
	void EnemyAttack2();	//�@����
	void EnemyAttack3();	//�o�i�i����
	void EnemyAttack4();	//�T������
	void EnemyFly();		//�W�����v����

	void InitAllState();	//�S��ԋ���
	void InitSleepState();
	void InitFlyState();

	void CreateBanana();
	void CreateMonkey();

};
