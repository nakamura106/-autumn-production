#pragma once



#include"../Object/Definition.h"
#include"../Object/ObjectBase.h"
#include"../Texture/Texture.h"
#include"../Bullet/PlayerBullet.h"
#include<vector>

const float G_PLAYER_SIZE = 256.0f;

class PlayerBase :public ObjectBase
{
public:
	PlayerBase();
	~PlayerBase();
	//!< �������֐�
	virtual void Init() = 0;
	virtual void CreateBullets(PlayerBulletType bullettype);
	void Create();
	
	//!< �A�b�v�f�[�g�֐�(�����X�V�p)
	virtual void Update();
	//!< �`��֐�(�I�u�W�F�N�g�x�[�X�ł܂Ƃ߂Ă��\��)
	void Draw();
	//!< �v���C���[�R���g���[���֐�(�v���C���[�̑���)
	void P_Controll();
	//!< �v���C���[�̃W�����v�����֐�
	virtual void Jump();
	//!< �e���˒������𒴂����特���X�g�b�N�������֐�
	void ReleaseNote();
	//��ԑJ��
	void ChangeState();
	
	void HitAction(ObjectRavel ravel_, float hit_use_atk_);

	virtual void InitWaitState();		
	virtual void InitMoveState();		
	virtual void InitJumpState();		
	virtual void InitJumpAttackState();	
	virtual void InitJumpDamageState();	
	virtual void InitDamageState();		
	virtual void InitAttackState();		
	virtual void InitMoveAttackState();
	virtual void InitThinkState();		
	virtual void InitDeathState();		
	virtual void InitClearState();		
	virtual void InitAllState();

	void Atkjudge();

	void BulletControl();

	void Attack();

	// �G�t�F�N�g�֌W�֐��܂Ƃ߂������̊֐�
	void AllInitEffect();
	void AllUpdateEffect();
	void AllDrawEffect();

	void CollisionParamUpdate()override;

protected:
	bool	m_do_jump;						//�W�����v����
	bool	m_is_miss;
	bool	m_is_active;					//�����Ă��邩�̔���
	bool	m_play_note[2];					//��������
	bool	m_do_bullet_firing;				//�U������p
	bool	m_is_release;					//�����J������p
	bool	m_do_attack;					//
	int		m_hp;							//�̗�
	int		m_List;							//�e�N�X�`���[���X�g�ۑ��p
	int		m_Key;							//�������Z����
	int     m_i;							//�A�j���[�V�����؂�ւ��p
	int		m_play_note_timer;				//���������p�^�C�}�[
	int		m_release_timer;				//�����J����p�^�C�}�[
	int		m_animtimer;
	int		m_effect;
	int		m_effecttimer;
	float   m_floorpos;

	int notebox[3];

	std::vector<PlayerBullet*> bullet_list;

	
private:
	const float M_BULLET_SPEED = 7.f;
};