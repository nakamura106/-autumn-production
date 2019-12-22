#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_

#include "BulletBase.h"

class EnemyBullet :public BulletBase
{
public:
	EnemyBullet(float x_, float y_, float move_speed_, Direction direction_);
	~EnemyBullet();
	void Init();

private:
	const int M_EBULLET_ANIM_SPLIT_ALL	= 1;
	const int M_EBULLET_ANIM_SPLIT_W	= 2;
	const int M_EBULLET_ANIM_SPLIT_H	= 1;

};

#endif
