#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_
#include"../Engine/Graphics.h"

#include "Definition.h"
#include "../Texture/Texture.h"

class ObjectBase {
public:
	ObjectBase();
	ObjectBase(ObjectRavel obj_ravel_, Direction direction_, float speed_);
	~ObjectBase();

	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Update();
	virtual void Draw();

	//���W�Q�b�^�[
	Position GetPos() { return m_pos; }
	//�폜����Q�b�^�[
	bool GetIsDelete() { return m_is_delete; }


	float GetHitUseAtk() { return m_hit_use_atk; }

	float GetMapPos() { return m_map_pos; };


	ObjectRavel GetRavel();	// ���x������

	HitRectangle GetRectParam();

	//12/10�@���ȓ����蔻�茋�ʒʒm�֐�
	virtual void HitAction(ObjectRavel ravel_,float hit_use_atk_){}

protected:
	/*�����摜�̃A�j���[�V�����p�֐�*/
	void AnimationUpdate();
	/*�A�j���[�V�����i�s�Q�b�^�[*/
	int GetAnimationTexNum();

	ObjectRavel		m_obj_ravel;	//���x��
	Position		m_pos;			//���W
	DrawParam		m_draw_param;	//�`��p�\����
	AnimationParam	m_anim_param;	//�A�j���[�V�����p�\����
	HitRectangle	m_rect_param;	//�����蔻��p�\����

	int m_direction;		//����(enum Direction���g�p)
	bool m_is_delete;		//�폜����p
	bool m_is_invincible;	//���G���
	int m_state;			//���
	float m_speed;			//�ړ����x


	float m_hit_use_atk;	//�����蔻�莞�Ɏg�p����U����

	float	m_map_pos;						//�}�b�v�����Œ�p


	//�f�o�b�O�p�ϐ�(12/2�c���ǉ�)
	int m_animation_timer;
	bool m_animation_end;	//�A�j���[�V�����̍Ōォ�ǂ���

	virtual void SetRectangle();	// �����蔻��\���̃p�����[�^�ݒ�֐��@��ŏ���
	
};

#endif

