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
	/*�`��*/
	void Draw();
	/*�A�j���[�V���� �c���ǉ�*/ 
	void AnimationUpdate();

	/*��Ԃ̍X�V*/
	virtual void UpdateState();

	/*
		��ԑJ��
	*/
	virtual void ChangeState();

	/*�ҋ@��Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromWait();
	/*�ړ���Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromWalk();
	/*�U����Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromAttack();
	/*�ǐՏ�Ԃ���̑J��*/
	virtual EnemyStateType ChangeStateFromChase();

	/*
		��Ԃ̏���
	*/
	/*�ҋ@*/
	virtual void EnemyIdle();
	/*�ǐՉE*/
	virtual void EnemyChase_R();
	/*�ǐՍ�*/
	virtual void EnemyChase_L();
	/*�ړ�*/
	virtual void EnemyMove();
	/*����(��J��)*/
	virtual void EnemyRefuge();
	/*�U��*/
	virtual void EnemyAttack();
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
	/*�U����̏���*/
	virtual void BackBeforeAttackState();

private:
	/*�f�o�b�O(������)�p �c���ǉ�*/
	int m_anim_timer;					//�A�j���[�V�������̃t���[���v���p�^�C�}�[
	const int	M_ANIM_FLAME = 10;		//�摜�ύX���s���t���[������
	const int	M_ANIM_TEX_ALL = 10;	//�摜�̃A�j���[�V��������
	const int	M_ANIM_TEX_WIDTH = 5;	//���̕�����
	const int	M_ANIM_TEX_HEIGHT = 2;	//�c�̕�����
	const float M_ENEMY_SYZE = 1024.f;	//�e�N�X�`���̃T�C�Y(�{���͏c��������)

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

	/*�A�j���[�V�����p �c���ǉ�*/
	int m_anim_tex_w;	//�����摜�̉�������
	int m_anim_tex_h;	//�����摜�̏c������
	int m_anim_tex_all;	//�����摜�̎g�p���镪���摜����(�󔒂͊܂߂Ȃ�)

};


#endif
