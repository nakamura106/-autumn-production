#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_
#include"../Engine/Graphics.h"

#include "Definition.h"
#include "../Texture/Texture.h"

class ObjectBase {
public:
	ObjectBase();
	~ObjectBase();

	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Update() = 0;
	virtual void Draw();

	//���W�Q�b�^�[
	Position GetPos() { return m_pos; }
	//�폜����Q�b�^�[
	bool GetIsDelete() { return m_is_delete; }

protected:
	/*�����摜�̃A�j���[�V�����p�֐�*/
	void AnimationUpdate();
	/*�A�j���[�V�����i�s�Q�b�^�[*/
	int GetAnimationTexNum();

	Position		m_pos;			//���W
	DrawParam		m_draw_param;	//�`��p�\����
	AnimationParam	m_anim_param;	//�A�j���[�V�����p�\����

	int m_direction;		//����(enum Direction���g�p)
	bool m_is_delete;		//�폜����p
	bool m_is_invincible;	//���G���
	int m_state;			//���
	float m_speed;			//�ړ����x

	//�f�o�b�O�p�ϐ�(12/2�c���ǉ�)
	int m_animation_timer;
	bool m_animation_end;	//�A�j���[�V�����̍Ōォ�ǂ���
	
};

#endif

