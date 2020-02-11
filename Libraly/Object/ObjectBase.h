	#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_
#include"../Engine/Graphics.h"

#include "../Effect/EffectBase.h"
#include "Definition.h"
#include "../Texture/Texture.h"
#include "../Collision/ShapeBase.h"

#include <vector>
#include <list>

class EffectBase;

class ObjectBase {
public:
	ObjectBase();
	ObjectBase(ObjectRavel obj_ravel_, Direction direction_, float speed_, int draw_angle_);
	ObjectBase(
		float pos_x_,
		float pos_y_,
		float size_x_,
		float size_y_,
		int tex_split_w_,
		int tex_split_h_,
		int tex_split_all,
		ObjectRavel obj_ravel_, 
		Direction direction_, 
		float speed_, 
		int draw_angle_, 
		bool is_turn_
	);
	~ObjectBase();

	virtual void Init() = 0;
	
	virtual void Update();
	virtual void Draw();

	/*		�Q�b�^�[		*/
	/*���W�Q�b�^�[*/
	Position GetPos() { return m_pos; }
	/*�폜����Q�b�^�[*/
	bool GetIsDelete() { return m_is_delete; }
	/*�����蔻�莞�Ɏg�p����l��Ԃ�*/
	float GetHitUseAtk() { return m_hit_use_atk; }

	/*�����蔻�莞�Ɏg�p����l��Ԃ��FNewVer 1/23*/
	/*
		���������I�u�W�F�N�g��n�����Ƃł��̃I�u�W�F�N�g�ɉ������l��Ԃ�
		(�I�[�o�[���C�h���Ċe�I�u�W�F�N�g���ݒ�)
	
	*/
	virtual float GetHitUseAtk(ObjectRavel hit_obj_) {
		return m_hit_use_atk;
	}

	/*�}�b�v��̍��W(���[���h���W)��Ԃ�*/
	float GetMapPos() { return m_map_pos; };
	/*Object���x���Q�b�^�[*/
	ObjectRavel GetRavel(){ return m_obj_ravel; }
	/*�����蔻��p�\���̃Q�b�^�[*/
	HitRectangle GetRectParam(){ return m_rect_param; }

	//�v���C���[��p���S�Q�b�^�[
	Position GetPlayerCenter();

	//�c���̉摜�؂蔲���T�C�Y�������ꍇ
	Position GetCenter(float splitsize_);

	//�c���̉摜�؂蔲���T�C�Y���Ⴄ�ꍇ
	Position GetCenter(float splitsizeX_,float splitsizeY_);

	int GetDirection() { return m_direction; }

	//12/10�@���ȓ����蔻�茋�ʒʒm�֐�
	virtual void HitAction(ObjectRavel ravel_,float hit_use_atk_){}

	/*�A�j���[�V�����i�s�Q�b�^�[*/
	int GetAnimationTexNum();

	// �����蔻�胊�X�g�̃Q�b�^�[�@collisionmanager�Ŏg�p
	std::list<ShapeBase*> GetShapeList() { return m_shape_list; }

	// Collision�pUpdate�܂Ƃߊ֐�
	virtual void CollisionParamUpdate(){}

private:

protected:

	/*�����摜�̃A�j���[�V�����p�֐�*/
	void AnimationUpdate();

	/*�}�b�v�̓����ɍ��킹�Ĉʒu����*/
	void CalcDrawPosition();

	/*�����蔻��\���̃p�����[�^�ݒ�֐��@��ŏ���*/
	virtual void SetRectangle();

	/*�n�ʂɂ��邩�ǂ����̔���*/
	bool CheckLandGround();

	/*		�\���̕ϐ�		*/
	Position		m_pos;			//���W
	Position		m_P_Center;
	Position		m_Tex_Center;
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
	bool		m_is_turn;			//�摜���]�����邩�ǂ���

	std::vector<EffectBase*> m_effect_list;	// �G�t�F�N�g�ۑ��p�z��
	std::list<ShapeBase*> m_shape_list;// �����蔻��p���X�g
};

#endif

