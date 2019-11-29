#pragma once

#include"../Object/ObjectBase.h"
#include"../Object/Definition.h"

class Map:public ObjectBase
{
public:
	Map();
	~Map();
	void Init();
	void Load();
	void Update();
	void MapScroll();
	void Draw();
	void Create(){}

private:
	Position m_pos;			//���W
	DrawParam m_draw_param;	// �`��p�\����
	float m_speed;			//�}�b�v�̃X�N���[�����x



};
