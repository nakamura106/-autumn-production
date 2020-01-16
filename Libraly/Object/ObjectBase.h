#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_
#include"../Engine/Graphics.h"

#include "../Effect/EffectBase.h"
#include "Definition.h"
#include "../Texture/Texture.h"

#include <vector>

class EffectBase;

class ObjectBase {
public:
	ObjectBase();
	ObjectBase(ObjectRavel obj_ravel_, Direction direction_, float speed_, int draw_angle_);
	~ObjectBase();

	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Update();
	virtual void Draw();

	/*		�Q�b�^�[		*/
	/*���W�Q�b�^�[*/
	Position GetPos() { return m_pos; }
	/*�폜����Q�b�^�[*/
	bool GetIsDelete() { return m_is_delete; }
	/*�����蔻�莞�Ɏg�p����l��Ԃ�*/
	float GetHitUseAtk() { return m_hit_use_atk; }
	/*�}�b�v��̍��W(���[���h���W)��Ԃ�*/
	float GetMapPos() { return m_map_pos; };
	/*Object���x���Q�b�^�[*/
	ObjectRavel GetRavel(){ return m_obj_ravel; }
	/*�����蔻��p�\���̃Q�b�^�[*/
	HitRectangle GetRectParam(){ return m_rect_param; }

	//12/10�@���ȓ����蔻�茋�ʒʒm�֐�
	virtual void HitAction(ObjectRavel ravel_,float hit_use_atk_){}

	/*�A�j���[�V�����i�s�Q�b�^�[*/
	int GetAnimationTexNum();

private:

protected:

	/*�����摜�̃A�j���[�V�����p�֐�*/
	void AnimationUpdate();

	/*�}�b�v�̓����ɍ��킹�Ĉʒu����*/
	void CalcDrawPosition();

	/*�����蔻��\���̃p�����[�^�ݒ�֐��@��ŏ���*/
	virtual void SetRectangle();

	/*		�\���̕ϐ�		*/
	Position		m_pos;			//���W
	DrawParam		m_draw_param;	//�`��p�\����
	AnimationParam	m_anim_param;	//�A�j���[�V�����p�\����
	HitRectangle	m_rect_param;	//�����蔻��p�\����

	/*		�P�̕ϐ��Q		*/
	ObjectRavel	m_obj_ravel;		//���x��
	int			m_direction;		//����(enum Direction���g�p)
	bool		m_is_delete;		//�폜����p
	bool		m_is_invincible;	//���G���
	int			m_state;			//���
	float		m_speed;			//�ړ����x
	float		m_hit_use_atk;		//�����蔻�莞�Ɏg�p����U����
	float		m_map_pos;			//�}�b�v�����Œ�p
	int			m_animation_timer;	//�A�j���[�V�����^�C�}�[
	bool		m_is_animation_end;	//�A�j���[�V�����̍Ōォ�ǂ���
	int			m_draw_angle;		//�`�悷��p�x

	std::vector<EffectBase*> m_effect_list;	// �G�t�F�N�g�ۑ��p�z��
};

#endif

