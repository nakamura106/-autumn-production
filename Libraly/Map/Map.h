#pragma once

#include"../Object/ObjectBase.h"
#include"../Object/Definition.h"

class Map:public ObjectBase
{
public:
	Map();
	~Map();
	void Init()override;
	void Load()override;
	void Update()override;
	void Draw()override;
	void MapScroll(int direction_);
	void HitJudgement();
	void Create(){}

private:
	Position m_pos;			//���W
	DrawParam m_draw_param;	// �`��p�\����
	float m_speed;			//�}�b�v�̃X�N���[�����x



};
