#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(float x_, float y_, float move_speed_, Direction direction_)
	:BulletBase(x_, y_, move_speed_, direction_)
{
	m_draw_param.texture_id = GameCategoryTextureList::GameEnemy_Bullet_Needle;
	m_anim_param.split_all = 1;
	m_anim_param.split_width = 2;
	m_anim_param.split_height = 1;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Init()
{
}
