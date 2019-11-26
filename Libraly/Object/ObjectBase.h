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
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw();

protected:
	Position m_pos;			//���W
	DrawParam m_param;		// �`��p�\����
	int m_direction;		//����
	bool m_is_delete;		//�폜����p
	bool m_is_invincible;	//���G���
	int m_state;			//���
	int m_flame_count;		//�t���[���J�E���g
	float m_centerX;		//X���S
	float m_centerY;		//Y���S
	float m_sprite_width;	//�摜�̉���
	float m_sprite_height;	//�摜�̍���
	float m_range;			//�˒�����
	float m_speed;			//��������
	float m_tu;
	float m_tv;

};

#endif

