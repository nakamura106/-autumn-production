#ifndef PLAYERBULLET_H_
#define PLAYERBULLET_H_

#include "BulletBase.h"

class PlayerBullet :public BulletBase
{
public:
	PlayerBullet(float x_, float y_, float move_speed_, Direction direction_, PlayerBulletType p_bullet_type_=PlayerBulletType::Chocho_1);
	~PlayerBullet();
	void Load();

	virtual void Draw();
	void Update();

	void CollisionParamUpdate()override;

private:
	const int	M_PBULLET_ANIM_SPLIT_ALL	= 16;
	const int	M_PBULLET_ANIM_SPLIT_W		= 4;
	const int	M_PBULLET_ANIM_SPLIT_H		= 4;
	const float M_CHOCHO_1_NUM				= 10.f;
	const float M_CHOCHO_2_NUM				= 10.f;
	const float M_TANCHO_1_NUM				= 6.f;
	const float M_TANCHO_2_NUM				= 6000.f;

	PlayerBulletType player_bullet_type;	

	/*’e‚Ìí—Ş‚É‚æ‚Á‚Äî•ñ‚ğİ’è*/
	void SetPlayerBulletInfo();

	/*“–‚½‚è‚Ìˆ—*/
	void HitAction(ObjectRavel ravel_, float hit_use_atk_);

};

#endif
