#pragma once
#include"EnemyBullet.h"


class MonkeyBullet :public EnemyBullet {
public:
	MonkeyBullet(
		float x_,
		float y_,
		float move_speed_,
		Direction direction_,
		float move_speed_y_ = 0.f,
		float acceleration_y_ = 5.f,
		GameCategoryTextureList use_tex_ = GameCategoryTextureList::GameEnemy_Bullet_Normal,
		int tex_split_w_ = 2,
		int tex_split_h_ = 1,
		int tex_split_all = 1
	);
	~MonkeyBullet();

private:
	void MoveUpdate();
	bool m_is_jump;
	float m_init_speed_y;

};
