#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Object/ObjectBase.h"
#include"../Engine/FlameTimer.h"
#include"../Bullet/EnemyBullet.h"
#include"../Engine/FileLoader.h"
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
	EnemyBase(
		float speed_, 
		EnemyID enemy_id_, 
		int max_wave_, 
		float tex_size_,
		int tex_split_w_ = 4,
		int tex_split_h_ = 4,
		int tex_split_all_ = 12
	);

	virtual ~EnemyBase();
	
	/*�`��֐�*/
	void Draw();

	/*������*/
	virtual void Init();

	/*�X�V*/
	virtual void Update();

	/*			�Q�b�^�[�Q			*/

	/*��Ԏ擾*/
	EnemyStateType	GetEnemyState() { return m_state; }

	/*�e�N�X�`���̎�̈ʒu��Ԃ�*/
	Position GetHandPos();

	/*�����蔻�莞�̒l��Ԃ�*/
	virtual float GetHitUseAtk(ObjectRavel hit_obj_);

	//�Q�[�W��Level
	enum class EnemyGageStage :int {
		Zero,
		Quarter,
		Half_Down,
		Half_Up,
		Almost,
		Max
	};

private:

	using EnemyAIList = std::vector < EnemyAIParam* >;
	using EnemyBulletList = std::vector<EnemyBullet*>;

	/*�������p�����l*/
	const int	M_ANIM_TEX_ALL					= 12;		//�摜�̃A�j���[�V��������
	const int	M_ANIM_TEX_WIDTH				= 4;		//���̕�����
	const int	M_ANIM_TEX_HEIGHT				= 4;		//�c�̕�����
	const int	M_AUTO_CHANGE_GAGE_FLAME		= 60;		//�Q�[�W�����񕜂̃t���[������
	const int	M_STOP_AUTO_SLEEP_TIME_DEFAULT	= 600;		//�Q�[�W�����񕜂��~�߂�t���[������
	const int	M_STOP_AUTO_SLEEP_TIME_HITBULLET = 120;		//�v���C���[�e�����蔻�莞�̃Q�[�W�����񕜂��~�߂�t���[������
	const float M_MOVE_LIMIT_X					= 4000.f;	//�ړ��ł���x���̍ő�l
	const float M_AUTO_SLEEP_UP_MAX_SPEED		= 7.f;		//���C�����������x�l(��J�xMAX)
	const float M_AUTO_SLEEP_UP_HIGH_SPEED		= 5.f;		//���C�����������x�l(��J�x1/4�ȏ�)
	const float M_AUTO_SLEEP_UP_MEDIUM_SPEED	= 3.5f;		//���C�����������x�l(��J�x�����ȏ�)
	const float M_AUTO_SLEEP_UP_LOW_SPEED		= 1.f;		//���C�����������x�l(��J�x3/4�ȏ�)
	const float M_AUTO_FATIGUE_DOWN_LOW_SPEED	= 0.5f;		//��J�����������x�l(��J�x4/3�ȏ�)
	const int	M_FATIGUE_GAGE_STAGE_NUM		= 4;		//��J�x�Q�[�W�̒i�K��
	const int	M_SLEEP_GAGE_STAGE_NUM			= 4;		//���C�Q�[�W�̒i�K��
	const float M_WAVE_CHANGE_MOVE_LIMIT		= 2500.f;	//wave�J�ڂ���ۂ̈ړ���
	const float	M_TEX_FRONT_SPACE				= 50.f;		//�e�N�X�`���T�C�Y�̑O������
	
	/*�������Ă���e�̊Ǘ�������֐��FUpdate�ŌĂяo���Ă���*/
	void BulletControl();

	/*�f�o�b�O�p�֐��F�L�[���͂ɂ����Enemy���ω�*/
	void DebugKeyAction();

	/*�f�[�^�o���N�ւ̒l�n��*/
	void DataSetUpdate();

	/*�f�[�^�o���N����̒l�̎擾*/
	void DataGetUpdate();

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
	int				m_transition_num;			//��ԑJ�ڎ��Ɏg�p����l�̃R�s�[
	int				m_savetime_wavechange;
	
	EnemyAIList		m_ai_list[static_cast<int>(EnemyAIType::EnemyAIType_Max)];	//AI�̃p�^�[�����i�[���ꂽ���X�g

	// �G�t�F�N�g�֌W�֐��܂Ƃ߂��֐�
	void AllInitEffect();
	void AllUpdateEffect();
	void AllDrawEffect();

	void CollisionParamUpdate()override;

protected:
	const float M_SKY_HEIGHT = 0.f;		//��s���x
	const int	M_ANIM_FLAME = 7;		//�摜�ύX���s���t���[������:7

	/*��ԑJ�ځEAI�ύX�W��֐��F������Ăяo����OK!(��ԑJ�ڂ���)*/
	void CompleteChangeState();

	/*�匳�̏�ԑJ�ڊ֐��F�����œn������ԂɑJ��*/
	void ChangeState(EnemyStateType next_state_);

	/*AI�ύX�֐��F�߂�l�Ŗ߂���AI�ɕύX����*/
	virtual EnemyAIType ChangeAIType() = 0;


	/*			��ԍX�V			*///���A�V��ԑJ�ڂǂ���ł��g�p

	virtual void EnemyWait() {}		//�ҋ@���
	virtual void EnemyMove();		//�ړ����
	virtual void EnemyRefuge() {}	//�������
	virtual void EnemyAttack1() {}	//�U����ԂP
	virtual void EnemyAttack2() {}	//�U����ԂQ
	virtual void EnemyAttack3() {}	//�U����ԂR
	virtual void EnemyRest() {}		//�x�e��ԁH
	void		 EnemySleep();		//������
	virtual void EnemyFly();		//��s���
	virtual void EnemyDead();		//���S���
	virtual void EnemyAttack4(){}	//�U�����4


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
	void		 InitAttack4State();//�U����ԂS

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


	/*		Wave�J�ڂ̍ۂ̏���		*/	

	//������
	void WaveChangeState1();
	//�߂��Ă���
	void WaveChangeState2();


	/*			�Q�[�W����			*/

	/*���C�x�̎�����*/
	virtual void DownSleepGage(float down_num_);
	/*��J�x�̎�����*/
	virtual void DownFatigueGage(float down_num_);
	/*���C�x�̑���*/
	virtual void UpSleepGage(float up_num_);
	/*��J�x�̑���*/
	virtual void UpFatigueGage(float up_num_);

	/*Wave�ύX����*/
	void ChangeWave();


	/*			�Q�b�^�[			*/

	/*��ԑJ�ڂ��Ă���̌o�ߎ��Ԏ擾*/
	int	GetStateSaveFlame();
	EnemyAIType GetNowAI() { return m_now_ai; }

	//�e�쐬
	Position GetShotPos(Direction direction_);
	
	/*
			�e�쐬�֐�
		<����>
		1 speed_x_		:x�������̈ړ���
		2 speed_y_		:y�������̈ړ���
		3 is_rotate_	:�ړ��ʂɉ����ĉ摜�̉�]���s�����ǂ���
		4 init_angle_	:�摜�̌��̉�]�x��(�������x��)

	*/
	void CreateBullet(
		Direction direction_,
		float speed_x_,
		float speed_y_ = 0.f,
		bool is_rotate_ = false,
		int init_angle_ = 0,
		GameCategoryTextureList use_tex_ = GameCategoryTextureList::GameEnemy_Bullet_Normal,
		int tex_all_ = 1,
		int tex_width_ = 2,
		int tex_height = 1,
		int use_tex_num_ = 0,
		float active_distance_ = 1000.f,
		bool is_animation_stop_ = true,
		float tex_size_ = 128.f
	);

	void SetAIType();

	/*			�S�G���ʂ̃p�����[�^			*/

	bool			m_is_flying;			//���ł��邩�ǂ���
	EnemyBulletList m_bullet_list;			//�e�̃��X�g
	Position		m_shot_adjust;			//�e���ˎ��̈ʒu�����p(���W����ǂꂭ�炢����Ă��邩)
	bool			m_animation_stop;		//true�̏ꍇ�A�A�j���[�V�������Ȃ�
	bool			m_do_bullet;			//�n�����˂��s�������ǂ���
	Position		m_hand_pos;				//��̈ʒu(�o�i�i�e�Ŏg�p)
	int				m_now_wave;				//���݂�wave
	int				m_max_wave;				//���̓G�̍ő�wave
	WaveState		m_wave_state;			//wave���
	EnemyGageStage	m_fatigue_gage_stage;	//��J�Q�[�W�̒i�K������ 0(�Q�[�W��0)�`5(�Q�[�W��MAX ���S)
	EnemyGageStage	m_sleep_gage_stage;		//���C�Q�[�W�̒i�K������ 0(�Q�[�W��0)�`5(�Q�[�W��MAX ����)
	float			m_player_center_pos;	//�v���C���[��x���W
	float			m_tex_space_front;		//���ʂ̋󔒕���������
	bool			m_do_deadly_ai;			//�K�E�Z���������ǂ����t���O
	bool			m_do_doraming;			//�h���~���O�����ǂ���

	bool m_is_debuff;						//���C�x�����񕜃X�g�b�v

};


#endif
