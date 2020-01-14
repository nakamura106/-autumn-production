#pragma once
#include"ShitBullet.h"

class BananaBullet :public ShitBullet {
public:
	BananaBullet(
		float x_,
		float y_,
		float move_speed_,
		float move_speed_y_,
		float acceleration_,
		Direction direction_,
		ObjectBase* parent_
	);
	void MoveUpdate();

private:
	ObjectBase* m_parent = nullptr;

};