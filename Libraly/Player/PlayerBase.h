#pragma once



#include"../Object/Definition.h"
#include"../Object/ObjectBase.h"
#include"../Engine/Texture.h"

class PlayerBase :public ObjectBase
{
public:
	PlayerBase();
	~PlayerBase();
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void P_Controll() = 0;
	virtual void InitAnimation()=0;
	virtual void DrawAnimation() = 0;
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

	UVANIMATION Animation[MaxAnimationNum];	//�A�j���[�V�����̃X�v���b�g�ۑ��p

	UVANIMATION clear_animation_Right[12];	//�A�j���[�V�����̖������Ⴄ�̂ŕ��u
	UVANIMATION clear_animation_Left[12];	//����
};