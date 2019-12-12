#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Object/ObjectBase.h"
#include"../Engine/FlameTimer.h"
#include"../Bullet/EnemyBullet.h"
#include<vector>
#include<string>

class EnemyBase :public ObjectBase
{
public:
	EnemyBase(float speed_, EnemyID enemy_id_);
	virtual ~EnemyBase();

	/*Load�p�֐��H�FObjectBase��������p����*/
	void Load() {}
	/*�`��֐�*/
	void Draw();
	/*������*/
	virtual void Init();
	/*�X�V*/
	virtual void Update();


	/*			�Q�b�^�[�Q			*/
	/*��Ԏ擾*/
	EnemyStateType	GetEnemyState() { return m_state; }
	
	

private:

	using EnemyAIList = std::vector < EnemyAIParam* >;

	/*�������p�����l*/
	const int	M_ANIM_FLAME		= 7;		//�摜�ύX���s���t���[������
	const int	M_ANIM_TEX_ALL		= 12;		//�摜�̃A�j���[�V��������
	const int	M_ANIM_TEX_WIDTH	= 4;		//���̕�����
	const int	M_ANIM_TEX_HEIGHT	= 4;		//�c�̕�����
	const float M_ENEMY_SYZE		= 1024.f;	//�e�N�X�`���̃T�C�Y(�{���͏c��������)
	const float	M_INIT_POS_X		= 700.f;	//����x���W
	const float M_INIT_POS_Y		= -70.f;	//����y���W
	const float M_CURE_SLEEP_TIME_DEFAULT = 30.f;		//�Q�[�W�����񕜂̃t���[������
	const int	M_STOP_AUTO_SLEEP_TIME_DEFAULT = 300;	//�Q�[�W�����񕜂��~�߂�t���[������
	const float M_MOVE_LIMIT_X = 2500.f;
	const int	M_GAMECLEAR_FLAME = 180;		//���胂�[�V�����J�ڌ�A�Q�[���N���A

	/*�������Ă���e�̊Ǘ�������֐��FUpdate�ŌĂяo���Ă���*/
	void BulletControl();		

	/*�f�o�b�O�p�֐��F�L�[���͂ɂ����Enemy���ω�*/
	void DebugKeyAction();

	/*�f�[�^�o���N�ւ̒l�n��*/
	void DataSetUpdate();

	/*�����莞�̏���*/
	void HitAction(ObjectRavel ravel_, float hit_use_atk_);

	/*�����Q�[�W�̎�����*/
	void AutoCureSleepGage();

	/*�ړ��͈͐���*/
	bool IsMoveLimitLeft();
	bool IsMoveLimitRight();
	void MoveLimitUpdate();

	/*���蔻��*/
	bool CheckSleepState();

	bool m_stop_state_transition;//CsvAI��ԑJ�ڂ��\���t���O�FDebugKeyAction�Ŏg�p

	//��Ԋ֌W
	EnemyStateType	m_state;					//�G�̏��
	int				m_state_saveflame;			//��Ԍp���̃t���[�����v���p
	float			m_state_save_pos_x;			//�ړ���������p
	Direction		m_player_pos_relationship;	//�v���C���[�Ƃ̈ʒu�֌W
	EnemyAIType		m_now_ai;					//���ݎg�p���Ă���AI
	int				m_now_ai_num;				//���ݎg�p���Ă���AI�̐i�s�x
	EnemyAIList		m_ai_list[static_cast<int>(EnemyAIType::EnemyAIType_Max)];	//AI�̃p�^�[�����i�[���ꂽ���X�g
	bool			m_is_pos_end;				//�}�b�v�̒[�܂ŗ�������true 12/10���ݎg�p����

	EnemyID			m_enemy_id;//�G��ID

	//�Q�[�W�֌W
	float			m_sleep_gauge;	//����Q�[�W
	float			m_fatigue_gauge;//��J�Q�[�W

	float m_auto_sleep_time;	//�񕜑��x
	int m_auto_sleep_saveflame;	//�񕜎��Ɍ��݂̃t���[�������i�[
	int m_stop_auto_sleep_time;	//�����񕜂��~�߂鎞��

	int m_game_clear_saveflame;	//�Q�[���N���A�܂ł̃t���[�����v���p

	//�e�֌W
	std::vector<EnemyBullet*> bullet_list;//�e�̃��X�g

protected:

	/*			�V��ԑJ��			*/
	/*
		�������FLoadAIState
	�@	���t���[���FUpdateAIState�EAITransitionUpdate
			��
		�J�ڊm�莞�FChangeAIState
			��
		��ԑJ�ڎ��FChangeState
		AI�ύX���FChangeAIType
	*/

	/*��ԍX�V�֐�:Csv���g�p����AI�V�X�e��(�ȉ��ACsvAI)�B12/10���݂͂�������g�p*/
	void UpdateAIState();

	/*csv�Ǎ��֐��F������AI�ԍ���.csv���������t�@�C����������*/
	//��FRes/Csv/Mouse/Enemy_AI1.csv��Res/Csv/Mouse/Enemy_AI
	void LoadAIData(std::string file_name_);

	/*AI�E��ԑJ�ڊ֐��FAI�������ɏ�Ԃ̑J�ڂ�AI�̕ύX���s��*/
	void ChangeAIState();

	/*�匳�̏�ԑJ�ڊ֐��F�����œn������ԂɑJ��*/
	void ChangeState(EnemyStateType next_state_);
	
	/*CsvAI��ԑJ�ڊ֐��F������AITransition�`�֐����Ăяo���Ă���*/
	void AITransitionUpdate();

	/*CsvAI��ԑJ�ڏ����Ǘ��֐��Ftrue��Ԃ��Ə�ԑJ�ڂƂ����d�g��*/
	bool AITransitionBase();		//���ʂ����ԑJ�ڏ���
	bool AITransitionStraight();	//�����ړ��ɂ���ď�ԑJ��
	bool AITransitionPassPlayer();	//�v���C���[���z����Ə�ԑJ��
	bool AITransitionFrontPlayer();	//�v���C���[��O�ɂ���Ə�ԑJ��
	bool AITransitionDistance();	//�w�肵�������ɂ���ď�ԑJ��
	bool AITransitionFlameTime();	//�w�肵�����Ԃɂ���ď�ԑJ��

	/*CsvAI�����ύX�֐��F��ԑJ�ڎ��A�����ύX*/
	void ChangeAIDirection();

	/*AI�ύX�֐��F�߂�l�Ŗ߂���AI�ɕύX����*/
	virtual EnemyAIType ChangeAIType() = 0;


	/*			��ԍX�V			*///���A�V��ԑJ�ڂǂ���ł��g�p

	virtual void EnemyWait();	//�ҋ@���
	virtual void EnemyChase();	//�ǐՏ��
	virtual void EnemyMove();	//�ړ����
	virtual void EnemyRefuge();	//�������
	virtual void EnemyAttack1();//�U����ԂP
	virtual void EnemyAttack2();//�U����ԂQ
	virtual void EnemyAttack3();//�U����ԂR
	virtual void EnemyRest();	//�x�e��ԁH
	void		 EnemySleep();	//������


	/*			��ԏ�����			*/

	virtual void InitAllState() {}	//�S��ԋ���
	virtual void InitWaitState();	//�ҋ@���
	virtual void InitWalkState();	//�ړ����
	virtual void InitRefugeState();	//�������
	virtual void InitAttack1State();//�U����ԂP
	virtual void InitAttack2State();//�U����ԂQ
	virtual void InitAttack3State();//�U����ԂR
	virtual void InitChaseState();	//�ǐՏ��
	virtual void InitSleepState();	//������



	/*			����ԑJ��			*/

	/*����ԍX�V�֐��F�V�X�e���͒P�������A�g�����������Ɣ��f*/
	void UpdateState();

	/*�e��Ԃ���̑J�ڊ֐�*/
	virtual EnemyStateType ChangeStateFromWait();	//�ҋ@���
	virtual EnemyStateType ChangeStateFromWalk();	//�ړ����
	virtual EnemyStateType ChangeStateFromRefuge();	//�������
	virtual EnemyStateType ChangeStateFromAttack1();//�U����ԂP
	virtual EnemyStateType ChangeStateFromChase();	//�ǐՏ��

	/*�����ύX�Fm_Direction��ύX���� LEFT��RIGHT*/
	void ChangeDirection();



	/*			�Q�[�W����			*/

	/*���C�x�̎�����*/
	virtual void CureSleepiness(float cure_sleep_);
	/*��J�x�̎�����*/
	virtual void CureFatigue(float cure_fatigue_);
	/*���C�x�̑���*/
	virtual void DamageSleepness(int damage_sleep_);
	/*��J�x�̑���*/
	virtual void DamageFatigue(int damage_fatigue_);


	/*			�Q�b�^�[			*/
	/*��ԑJ�ڂ��Ă���̌o�ߎ��Ԏ擾*/
	int	GetStateSaveFlame();
	EnemyAIType GetNowAI() { return m_now_ai; }

	//�e�쐬
	void CreateBullet(float pos_x_, float pos_y_, float move_speed_);

	/*			�S�G���ʂ̃p�����[�^			*/
	

};


#endif
