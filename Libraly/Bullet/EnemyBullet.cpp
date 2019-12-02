#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(float x_, float y_, float move_speed_, Direction direction_)
	:BulletBase(x_, y_, move_speed_, direction_)
{
}

EnemyBullet::~EnemyBullet()
{
}