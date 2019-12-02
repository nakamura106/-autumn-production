#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_

#include "BulletBase.h"

class EnemyBullet :public BulletBase
{
public:
	EnemyBullet(float x_, float y_, float move_speed_, Direction direction_);
	~EnemyBullet();

private:

};

#endif
