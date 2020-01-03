#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Object/ObjectBase.h"
#include"../Engine/FlameTimer.h"
#include"../Bullet/EnemyBullet.h"
#include<vector>
#include<string>

/*		�g����		*/
/*
	�������FLoadAIState
�@	���t���[���FUpdateAIState�EAITransitionUpdate
		��
	�J�ڊm�莞�FChangeAIState
		��
	��ԑJ�ڎ��FChangeState
	AI�ύX���FChangeAIType
*/

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
	using EnemyBulletList = std::vector<EnemyBullet*>;

	/*�������p�萔*/
	const float	M_PLAYER_SIZE_X = 256.f;	//�v���C���[��x�����̉摜�T�C�Y(�v���C���[�Ƃ̈ʒu�֌W�Ŏg�p)

	/*�������p�����l*/
	const int	M_ANIM_FLAME					= 7;		//�摜�ύX���s���t���[������
	const int	M_ANIM_TEX_ALL					= 12;		//�摜�̃A�j���[�V��������
	const int	M_ANIM_TEX_WIDTH				= 4;		//���̕�����
	const int	M_ANIM_TEX_HEIGHT				= 4;		//�c�̕�����
	const float M_ENEMY_SYZE					= 1024.f;	//�e�N�X�`���̃T�C�Y(�{���͏c��������)
	const float	M_INIT_POS_X					= 700.f;	//����x���W
	const float M_INIT_POS_Y					= -70.f;	//����y���W
	const int	M_CURE_SLEEP_TIME_DEFAULT		= 60;		//�Q�[�W�����񕜂̃t���[������
	const int	M_STOP_AUTO_SLEEP_TIME_DEFAULT	= 600;		//�Q�[�W�����񕜂��~�߂�t���[������
	const int	M_STOP_AUTO_SLEEP_TIME_HITBULLET = 120;		//�v���C���[�e�����蔻�莞�̃Q�[�W�����񕜂��~�߂�t���[������
	const float M_MOVE_LIMIT_X					= 3500.f;	
	const float M_FATIGUE						= 46.f;
	const float M_AUTO_SLEEP_UP_MAX_SPEED		= 2.f;
	const float M_AUTO_SLEEP_UP_HIGH_SPEED		= 1.2f;		//���C�����������x�l
	const float M_AUTO_SLEEP_UP_MEDIUM_SPEED	= 0.7f;
	const float M_AUTO_SLEEP_UP_LOW_SPEED		= 0.3f;
	const float M_AUTO_FATIGUE_DOWN_LOW_SPEED	= 0.3f;		//��J�x�����������x�l
	const int	M_FATIGUE_GAGE_STAGE_NUM		= 4;		//��J�x�Q�[�W�̒i�K��
	const int	M_SLEEP_GAGE_STAGE_NUM			= 4;		//���C�Q�[�W�̒i�K��
	const float M_SKY_HEIGHT					= -500.f;	//��s���x

	/*�������Ă���e�̊Ǘ�������֐��FUpdate�ŌĂяo���Ă���*/
	void BulletControl();		

	/*�f�o�b�O�p�֐��F�L�[���͂ɂ����Enemy���ω�*/
	void DebugKeyAction();

	/*�f�[�^�o���N�ւ̒l�n��*/
	void DataSetUpdate();

	/*�����莞�̏���*/
	void HitAction(ObjectRavel ravel_, float hit_use_atk_);

	/*�ړ��͈͐���*/
	bool IsMoveLimitLeft();
	bool IsMoveLimitRight();
	void MoveLimitUpdate();

	/*�Q�[�W�ő唻��*/
	bool CheckSleepGageMax();
	bool CheckFatigueGageMax();

	/*��J��ԁE���C(�C���C��)��Ԃ̎擾*/
	GageState CheckGaugeState();

	/*�Q�[�W�ʂ̍ő�Œ�Ǘ�*/
	void GaugeLimitControl();

	/*			�V��ԑJ��			*/

	/*��ԍX�V�֐�:Csv���g�p����AI�V�X�e��(�ȉ��ACsvAI)�B12/10���݂͂�������g�p*/
	void UpdateAIState();

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

	/*CsvAI���x�ݒ�֐�*/
	void SetGageStateSpeed();

	/*��J�Q�[�W�̗ʂɂ���ăQ�[�W�����񕜗ʂ�ω�������֐�*/
	void AutoChangeGageUpdate();
	int GageStageCalc(float now_gage_, float max_gage_, int gage_stage_num_);

	bool m_stop_state_transition;	//CsvAI��ԑJ�ڂ��\���t���O�FDebugKeyAction�Ŏg�p

	EnemyStateType	m_state;					//�G�̏��
	EnemyID			m_enemy_id;					//�G��ID
	EnemyAIType		m_now_ai;					//���ݎg�p���Ă���AI
	int				m_now_ai_num;				//���ݎg�p���Ă���AI�̐i�s�x
	int				m_stop_auto_sleep_time;		//�����񕜂��~�߂鎞��
	float			m_sleep_gauge;				//����Q�[�W
	float			m_fatigue_gauge;			//��J�Q�[�W
	int				m_auto_sleep_time;			//�񕜑��x
	float			m_state_save_pos_x;			//�ړ���������p
	Direction		m_p_pos_relation;			//�v���C���[�Ƃ̈ʒu�֌W
	int				m_savetime_auto_slpgauge;	//�t���[�����i�[�F���C�x�����񕜎��Ɏg�p
	int				m_savetime_end;				//�t���[�����i�[�F�����Ă���Q�[���N���A�܂łŎg�p
	int				m_savetime_state;			//�t���[�����i�[�F��Ԃ��p�����鎞�Ԍv�Z�Ŏg�p
	int				m_fatigue_gage_stage;		//��J�Q�[�W�̒i�K������
	int				m_sleep_gage_stage;			//���C�Q�[�W�̒i�K������

	EnemyAIList		m_ai_list[static_cast<int>(EnemyAIType::EnemyAIType_Max)];	//AI�̃p�^�[�����i�[���ꂽ���X�g
	EnemyBulletList bullet_list;		//�e�̃��X�g

protected:

	/*AI�ύX�֐��F�߂�l�Ŗ߂���AI�ɕύX����*/
	virtual EnemyAIType ChangeAIType() = 0;


	/*			��ԍX�V			*///���A�V��ԑJ�ڂǂ���ł��g�p

	virtual void EnemyWait() {}		//�ҋ@���
	//virtual void EnemyChase() {}	//�ǐՏ��
	virtual void EnemyMove();		//�ړ����
	virtual void EnemyRefuge() {}	//�������
	virtual void EnemyAttack1() {}	//�U����ԂP
	virtual void EnemyAttack2() {}	//�U����ԂQ
	virtual void EnemyAttack3() {}	//�U����ԂR
	virtual void EnemyRest() {}		//�x�e��ԁH
	void		 EnemySleep();		//������
	virtual void EnemyFly();		//��s���
	void		 EnemyDead();		//���S���


	/*			��ԏ�����			*/

	virtual void InitAllState();	//�S��ԋ���
	virtual void InitWaitState();	//�ҋ@���
	virtual void InitWalkState();	//�ړ����
	virtual void InitRefugeState();	//�������
	virtual void InitAttack1State();//�U����ԂP
	virtual void InitAttack2State();//�U����ԂQ
	virtual void InitAttack3State();//�U����ԂR
	virtual void InitChaseState();	//�ǐՏ��
	virtual void InitSleepState();	//������
	virtual void InitFlyState();	//��s���(���Ŏg�p)
	void		 InitDeadState();	//���S���

	/*csv�Ǎ��֐��F������AI�ԍ���.csv���������t�@�C����������*/
	//��FRes/Csv/Mouse/Enemy_AI1.csv��Res/Csv/Mouse/Enemy_AI
	void LoadAIData(std::string file_name_);

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
	virtual void DownSleepGage(float down_num_);
	/*��J�x�̎�����*/
	virtual void DownFatigueGage(float down_num_);
	/*���C�x�̑���*/
	virtual void UpSleepGage(float up_num_);
	/*��J�x�̑���*/
	virtual void UpFatigueGage(float up_num_);


	/*			�Q�b�^�[			*/
	/*��ԑJ�ڂ��Ă���̌o�ߎ��Ԏ擾*/
	int	GetStateSaveFlame();
	EnemyAIType GetNowAI() { return m_now_ai; }

	//�e�쐬
	void CreateBullet(float pos_x_, float pos_y_, float move_speed_);

	/*			�S�G���ʂ̃p�����[�^			*/
	bool m_is_flying;	//���ł��邩�ǂ���

};


#endif
