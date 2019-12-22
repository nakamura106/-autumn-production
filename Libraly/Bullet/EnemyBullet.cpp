#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(float x_, float y_, float move_speed_, Direction direction_)
	:BulletBase(x_, y_, move_speed_, direction_)
{
	m_draw_param.texture_id		= GameCategoryTextureList::GameEnemy_Bullet_Needle;
	m_anim_param.split_all		= M_EBULLET_ANIM_SPLIT_ALL;
	m_anim_param.split_width	= M_EBULLET_ANIM_SPLIT_W;
	m_anim_param.split_height	= M_EBULLET_ANIM_SPLIT_H;

	m_obj_ravel = ObjectRavel::Ravel_EnemyBullet;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Init()
{
}
