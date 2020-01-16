#pragma once
#include"ShitBullet.h"
#include"../Enemy/EnemyBase.h"

class EnemyBase;

class BananaBullet :public ShitBullet {
public:
	BananaBullet(
		float x_,
		float y_,
		float move_speed_,
		float move_speed_y_,
		float acceleration_,
		Direction direction_,
		EnemyBase* parent_,
		int move_start_anim_num_
	);
	void MoveUpdate();

private:
	EnemyBase* m_parent = nullptr;
	int m_move_start_anim_num;
	bool m_is_move;//“®‚¢‚½Œã‚Í‚±‚ê‚ªtrue

};