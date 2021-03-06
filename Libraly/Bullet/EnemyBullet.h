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
		float acceleration_y_ = 0.f,
		GameCategoryTextureList use_tex_ = GameCategoryTextureList::GameEnemy_Bullet_Normal,
		int tex_split_w_ = 2,
		int tex_split_h_ = 1,
		int tex_split_all_ = 1,
		int tex_use_num_ = 0,
		float active_distance_ = 1000.f,
		bool is_animation_stop_ = true,
		float tex_size_ = 128.f
	);

	~EnemyBullet();
	void Init();
	void Update();

	void CollisionParamUpdate()override;

	void HitAction(ObjectRavel ravel_, float hit_use_atk_);

private:
	const int M_EBULLET_ANIM_SPLIT_ALL	= 1;
	const int M_EBULLET_ANIM_SPLIT_W	= 2;
	const int M_EBULLET_ANIM_SPLIT_H	= 1;
	void CalcTexUseNum();

protected:
	float	m_acceleration_y;		//加速度
	int		m_tex_use_num;			//使用する画像枚数目
	bool	m_is_animation_stop;

};

#endif
