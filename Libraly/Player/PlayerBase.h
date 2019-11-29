#pragma once



#include"../Object/Definition.h"
#include"../Object/ObjectBase.h"
#include"../Engine/Texture.h"

class PlayerBase :public ObjectBase
{
public:
	PlayerBase();
	~PlayerBase();
	//!< �������֐�
	virtual void Init() = 0;
	//!< �摜�Ǎ��p�֐�(�Q�[���V�[���ɂׂ������\��)
	virtual void Load() = 0;
	//!< �A�b�v�f�[�g�֐�(�����X�V�p)
	virtual void Update() = 0;
	//!< �`��֐�(�I�u�W�F�N�g�x�[�X�ł܂Ƃ߂Ă��\��)
	virtual void Draw() = 0;
	//!< �v���C���[�R���g���[���֐�(�v���C���[�̑���)
	virtual void P_Controll() = 0;
	//!< �A�j���[�V�����̏������֐�
	virtual void InitAnimation()=0;
	//!< �A�j���[�V�����̕`��֐�(�摜���A�j���[�V���������邽�߂̊֐�)
	virtual void DrawAnimation() = 0;
	//!< �A�j���[�V�����̃A�b�v�f�[�g�֐�(��Ԃɂ���ăA�j���[�V������ς���֐� ��)
	virtual void UpdateAnimation() = 0;
	virtual void Jump() = 0;
	virtual void ReleaseNote() = 0;
	virtual void GetMotion(int Llist, int Rlist)=0;
	virtual Position GetPos() = 0;


protected:
	int		m_hp;							//�̗�
	bool	m_do_jump;						//�W�����v����
	bool	m_is_active;					//�����Ă��邩�̔���
	bool	m_play_note[6];					//��������
	int		m_List;							//�e�N�X�`���[���X�g�ۑ��p
	int		m_Key;							//�������Z����
	int     m_i;							//�A�j���[�V�����؂�ւ��p

	UVANIMATION Animation[MaxAnimationNum];	//�A�j���[�V�����̃X�v���b�g�ۑ��p

	UVANIMATION clear_animation_Right[12];	//�A�j���[�V�����̖������Ⴄ�̂ŕ��u
	UVANIMATION clear_animation_Left[12];	//����
};