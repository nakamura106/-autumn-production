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
	EnemyBase();
	EnemyBase(float speed_, EnemyID enemy_id_);
	virtual ~EnemyBase();

	void Load(){}
	void Draw();

	/*������*/
	virtual void Init();
	/*�X�V*/
	virtual void Update();

	/*
		�Q�b�^�[�Q
	*/
	/*��Ԏ擾*/
	virtual EnemyStateType GetEnemyState();

	/*
		�Q�[�W����
	*/
	/*���C�x�̎�����*/
	virtual void CureSleepiness();
	/*��J�x�̎�����*/
	virtual void CureFatigue();
	/*���C�x�̑���*/
	virtual void DamageSleepness(int damage_sleep_);
	/*��J�x�̑���*/
	virtual void DamageFatigue(int damage_fatigue_);
	/*�U����̏���*/
	virtual void BackBeforeAttackState();

private:
	/*�������p�����l*/
	const int	M_ANIM_FLAME		= 7;		//�摜�ύX���s���t���[������
	const int	M_ANIM_TEX_ALL		= 12;		//�摜�̃A�j���[�V��������
	const int	M_ANIM_TEX_WIDTH	= 4;		//���̕�����
	const int	M_ANIM_TEX_HEIGHT	= 4;		//�c�̕�����
	const float M_ENEMY_SYZE		= 1024.f;	//�e�N�X�`���̃T�C�Y(�{���͏c��������)
	const float	M_INIT_POS_X		= 700.f;	//����x���W
	const float M_INIT_POS_Y		= -100.f;	//����y���W

	bool m_can_state_transition;

	void BulletControl();

	void DebugKeyAction();

protected:

	/*
		��Ԃ̏���
	*/
	
	/*��Ԃ̍X�V*/
	//�����I�ɂ͔p�~�@AI�̃p�^�[�������d�l�ɕύX
	void UpdateState();

	void UpdateAIState();

	/*AIState�J��*/
	bool TransitionStraight();
	bool TransitionPassPlayer();
	bool TransitionFrontPlayer();
	bool TransitionDistance();
	bool TransitionFlameTime();

	/*�ҋ@*/
	virtual void EnemyWait();
	/*�ǐ�*/
	virtual void EnemyChase();
	/*�ړ�*/
	virtual void EnemyMove();
	/*����(��J��)*/
	virtual void EnemyRefuge();
	/*�U��*/
	virtual void EnemyAttack1();
	virtual void EnemyAttack2();
	virtual void EnemyAttack3();
	/*�x�e*/
	virtual void EnemyRest();

	/*
		��ԑJ��
		�f�o�b�O�p�Ƃ��Ďg�p
	*/

	/*��ԑJ�ڊ֐��A�FAI�������ɑJ��*/
	void ChangeAIState();

	/*AI�ύX�֐��F�߂�l�Ŗ߂���AI�ɕύX����*/
	virtual EnemyAIType ChangeAIType() = 0;

	/*��ԑJ�ڊ֐��@�F�����œn������ԂɑJ��*/
	void ChangeState(EnemyStateType next_state_);

	/*�ҋ@��Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromWait();
	/*�ړ���Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromWalk();
	/*������Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromRefuge();
	/*�U����Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromAttack1();
	/*�ǐՏ�Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromChase();

	/*
		��ԏ�����
	*/
	/*�ҋ@���*/
	virtual void InitWaitState();
	/*�ړ����*/
	virtual void InitWalkState();
	/*�������*/
	virtual void InitRefugeState();
	/*�U�����*/
	virtual void InitAttack1State();
	virtual void InitAttack2State();
	virtual void InitAttack3State();
	
	/*�ǐՏ��*/
	virtual void InitChaseState();
	/*������(�N���A�H)*/
	virtual void InitSleepState();

	/*�����ύX*/
	void ChangeDirection();

	/*�U�����p�[�g���[�̏�����*/
	//virtual void InitAttackRepertory() = 0;

	/*csv�t�@�C���ǂݍ���*/
	//������AI�̔ԍ���.csv��������
	//�t�@�C����������
	//��FRes/Csv/EnemyAI1.csv��Res/Csv/EnemyAI
	void LoadAIData(std::string file_name_);

	float	m_sleep_gauge;		//����Q�[�W
	float	m_fatigue_gauge;	//��J�Q�[�W
	int		m_time_of_break;	//�x�e����
	bool	m_is_break;			//�x�e���Ă��邩
	bool	m_is_hit_judge;		//�����蔻�肪���݂��邩
	int		m_refuge_time;		//������鎞��
	int		m_atk_time_count;	//�U���Ԋu�J�E���^�[

	EnemyID					m_enemy_id;				//�G��ID
	EnemyStateType			m_state;				//�G�̏��
	int						m_attack_repertory;		//�U���̃o���G�[�V����

	int		m_state_saveflame;	//��Ԍp���̃t���[�����v���p

	std::vector<EnemyBullet*> bullet_list;
	std::vector<EnemyAIParam*> m_ai_list[(int)EnemyAIType::EnemyAIType_Max];		//AI�̃p�^�[�����i�[���ꂽ���X�g
	EnemyAIType m_now_ai;		//���ݎg�p���Ă���AI
	int m_now_ai_num;	//���ݎg�p���Ă���AI�̐i�s�x

};


#endif
