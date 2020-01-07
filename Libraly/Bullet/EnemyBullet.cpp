#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(
	float x_,
	float y_,
	float move_speed_,
	Direction direction_,
	GameCategoryTextureList use_tex_,
	int tex_split_w_,
	int tex_split_h_,
	int tex_split_all
)
	:BulletBase(x_, y_, move_speed_, direction_)
{

	m_draw_param.texture_id		= use_tex_;
	m_anim_param.split_all		= tex_split_all;
	m_anim_param.split_width	= tex_split_w_;
	m_anim_param.split_height	= tex_split_h_;
	m_obj_ravel					= ObjectRavel::Ravel_EnemyBullet;

}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::Init()
{

}
