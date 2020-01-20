#pragma once
#include"EnemyBase.h"


class Gorilla :public EnemyBase {
public:
	Gorilla();
	~Gorilla();
	void Init();

private:
	const std::string M_AIDataFileName = "Res/Csv/Gorilla/Enemy_AI";
	const float		  M_JUMP_ACCELERATION_DEFAULT = 0.4f;
	const int		M_JUMP_STOP_ANIM_FLAME = 4;
	const float		  M_JUMP_SPEED_DEFAULT = 15.f;
	const float		M_SHOT_ADJUST_X_INPACT = 220.f;
	const int		M_ATTACK2_ANIM_TEX_NUM = 13;
	const float		M_INPACT_RIGHT_B_ADJUST = -70.f;
	const float		M_INPACT_LEFT_B_ADJUST = -170.f;
	const float		M_INPACT_ACTIVE_DISTANCE = 600.f;

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
