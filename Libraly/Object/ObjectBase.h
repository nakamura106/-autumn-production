#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_
#include"../Engine/Graphics.h"

#include "Definition.h"

class ObjectBase {
public:
	ObjectBase();
	~ObjectBase();

	virtual void Init() = 0;
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	Position m_pos;			  //���W
	float m_speed;			  //��������
	bool m_is_delete;		  //�폜����p
	int m_direction;		  //����
	int m_state;			  //���
	int m_flame_count;		  //�t���[���J�E���g
	float m_centerX;		  //X���S
	float m_centerY;		  //Y���S
	float m_sprite_width;	  //�摜�̉���
	float m_sprite_height;	  //�摜�̍���
	float m_range;			  //�˒�����
	bool m_is_invincible;	  //���G���

};

#endif

