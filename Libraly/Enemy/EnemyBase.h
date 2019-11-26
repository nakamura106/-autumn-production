#ifndef ENEMYBASE_H_
#define ENEMYBASE_H_

#include "../Object/ObjectBase.h"

class EnemyBase :public ObjectBase
{
public:
	EnemyBase();
	~EnemyBase();

	/*������*/
	virtual void Init();
	/*�X�V*/
	virtual void Update();
	/*�`��*/
	virtual void Draw();

	/*��Ԃ̍X�V*/
	virtual void UpdateState();
	/*��Ԃ̑J��*/
	virtual void ChangeState();

	/*
		��Ԃ̏���
	*/
	/*�ړ�*/
	virtual void EnemyMove();
	/*����(��J��)*/
	virtual void EnemyRefuge();
	/*�U��*/
	virtual void EnemyAttack();
	/*�ҋ@*/
	virtual void EnemyIdle();
	/*�x�e*/
	virtual void EnemyBreak();

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

protected:

	float	m_sleep_gauge;		//����Q�[�W
	float	m_fatigue_gauge;	//��J�Q�[�W
	int		m_time_of_break;	//�x�e����
	bool	m_is_break;			//�x�e���Ă��邩
	bool	m_is_hit_judge;		//�����蔻�肪���݂��邩

	Enemy	m_Enemy_Id;			//�G��ID
	EnemyStateType m_State;		//�G�̏��
	EnemyAttackRepertory m_attack_repertory;	//�U���̃o���G�[�V����
	EnemytoPlayerState m_enemy_to_player_state;	//�v���C���[�Ƃ̊֌W�H

};


#endif
