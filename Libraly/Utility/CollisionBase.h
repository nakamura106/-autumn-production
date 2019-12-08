#pragma once

#include"../../Object/Definition.h"

class CollisionBase
{
public:
	CollisionBase() {};
	~CollisionBase() {};

	virtual void Init() = 0;
	virtual void Update() = 0;
	//�Ώۂ̃I�u�W�F�N�g�ɔ���p�̉~�Ȃǂ�z�u����
	virtual void Arrangement(float centerX, float centerY) = 0;

	Position GetPos() { return m_pos; };
	bool GetIsDelete() { return m_is_delete; };

protected:
	Position m_pos;
	bool m_is_delete;


};
