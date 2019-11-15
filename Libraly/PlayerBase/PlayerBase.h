#pragma once

#pragma once

#include"../Object/Definition.h"
#include"../Object/ObjectBase.h"

class PlayerBase :public ObjectBase
{
public:
	PlayerBase();
	~PlayerBase();
	virtual void Init() = 0;
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	int m_hp;				//�̗�
	int m_direction;		//����
	int m_state;			//�v���C���[�̏��
	int m_flamecount;		//�t���[���J�E���g(UV�X�N���[���p)
	float m_centerX;		//�摜��X���S
	float m_centery;		//�摜��Y���S
	float m_sprite_width;	//�摜�̉���
	float m_sprite_height;	//�摜�̏c��
	float m_range;			//�˒�����
	bool m_is_invincible;	//���G����
	
	
};
