#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(
	float x_,
	float y_,
	float move_speed_,
	Direction direction_,
	int draw_angle_,
	float move_speed_y_,
	GameCategoryTextureList use_tex_,
	int tex_split_w_,
	int tex_split_h_,
	int tex_split_all
)
	:BulletBase(x_, y_, move_speed_, direction_, ObjectRavel::Ravel_EnemyBullet, move_speed_y_, draw_angle_)
{

	m_draw_param.texture_id = use_tex_;
	m_anim_param.split_all = tex_split_all;
	m_anim_param.split_width = tex_split_w_;
	m_anim_param.split_height = tex_split_h_;

}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::Init()
{
	
}
