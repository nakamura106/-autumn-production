#include "BananaBullet.h"

BananaBullet::BananaBullet(
	float x_, 
	float y_, 
	float move_speed_, 
	float move_speed_y_, 
	float acceleration_, 
	Direction direction_, 
	ObjectBase* parent_
):ShitBullet(x_,y_,move_speed_,move_speed_y_,acceleration_,direction_,GameCategoryTextureList::GameEnemy_Bullet_Shit)
{
	m_parent = parent_;
}

void BananaBullet::MoveUpdate()
{
	//最初は親であるオブジェクトに従って動く
	

	ShitBullet::MoveUpdate();
}
