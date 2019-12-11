#ifndef PLAYERBULLET_H_
#define PLAYERBULLET_H_

#include "BulletBase.h"

class PlayerBullet :public BulletBase
{
public:
	PlayerBullet(float x_, float y_, float move_speed_, Direction direction_, PlayerBulletType p_bullet_type_=PlayerBulletType::Chocho_1);
	~PlayerBullet();
	void Load();

private:
	PlayerBulletType player_bullet_type;	

	void SetTextureID();

	/*“–‚½‚è‚Ìˆ—*/
	void HitAction(ObjectRavel ravel_, float hit_use_atk_);

};

#endif
