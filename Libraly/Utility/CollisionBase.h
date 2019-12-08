#pragma once

#include"../../Object/Definition.h"

class CollisionBase
{
public:
	CollisionBase() {};
	~CollisionBase() {};

	virtual void Init() = 0;
	virtual void Update() = 0;
	//対象のオブジェクトに判定用の円などを配置する
	virtual void Arrangement(float centerX, float centerY) = 0;

	Position GetPos() { return m_pos; };
	bool GetIsDelete() { return m_is_delete; };

protected:
	Position m_pos;
	bool m_is_delete;


};
