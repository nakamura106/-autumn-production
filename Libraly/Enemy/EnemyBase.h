#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Object/ObjectBase.h"

class EnemyBase :public ObjectBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	void Create() {}
	void Load(){}

	/*������*/
	virtual void Init();
	/*�X�V*/
	virtual void Update();

	/*��Ԃ̍X�V*/
	void UpdateState();

	/*
		��ԑJ��
	*/
	virtual void ChangeState();

	/*�ҋ@��Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromWait();
	/*�ړ���Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromWalk();
	/*������Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromRefuge();
	/*�x�e��Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromRest();
	/*�U����Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromAttack();
	/*�ǐՏ�Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromChase();

	/*
		��Ԃ̏���
	*/
	/*�ҋ@*/
	virtual void EnemyWait();

#if 0
	/*�ǐՉE*/
	virtual void EnemyChase_R();
	/*�ǐՍ�*/
	virtual void EnemyChase_L();
#endif

	/*�ړ�*/
	virtual void EnemyMove();
	/*����(��J��)*/
	virtual void EnemyRefuge();
	/*�U��*/
	virtual void EnemyAttack();
	/*�x�e*/
	virtual void EnemyRest();

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

protected:
	float	m_sleep_gauge;		//����Q�[�W
	float	m_fatigue_gauge;	//��J�Q�[�W
	int		m_time_of_break;	//�x�e����
	bool	m_is_break;			//�x�e���Ă��邩
	bool	m_is_hit_judge;		//�����蔻�肪���݂��邩
	int		m_refuge_time;		//������鎞��
	int		m_atk_time_count;	//�U���Ԋu�J�E���^�[
	float	m_speed;			//�X�s�[�h

	EnemyID	m_enemy_id;			//�G��ID
	EnemyStateType m_state;		//�G�̏��
	EnemyAttackRepertory m_attack_repertory;	//�U���̃o���G�[�V����
	EnemytoPlayerState m_enemy_to_player_state;	//�v���C���[�Ƃ̊֌W�H

};


#endif
