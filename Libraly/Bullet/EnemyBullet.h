#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_

#include "BulletBase.h"

class EnemyBullet :public BulletBase
{
public:
	EnemyBullet(
		float x_,
		float y_,
		float move_speed_,
		Direction direction_,
		int draw_angle_ = 0,
		float move_speed_y_ = 0.f,
		GameCategoryTextureList use_tex_ = GameCategoryTextureList::GameEnemy_Bullet_Normal,
		int tex_split_w_ = 2,
		int tex_split_h_ = 1,
		int tex_split_all = 1
	);

	~EnemyBullet();
	void Init();

private:
	const int M_EBULLET_ANIM_SPLIT_ALL	= 1;
	const int M_EBULLET_ANIM_SPLIT_W	= 2;
	const int M_EBULLET_ANIM_SPLIT_H	= 1;

};

#endif
