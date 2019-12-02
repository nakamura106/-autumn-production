#ifndef PLAYERBULLET_H_
#define PLAYERBULLET_H_

#include "BulletBase.h"

class PlayerBullet :public BulletBase
{
public:
	PlayerBullet(float x_, float y_, float move_speed_, Direction direction_);
	~PlayerBullet();

private:

};

#endif
