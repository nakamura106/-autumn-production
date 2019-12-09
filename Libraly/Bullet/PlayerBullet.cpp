#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(float x_, float y_, float move_speed_, Direction direction_)
	:BulletBase(x_, y_, move_speed_, direction_)
{
	m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_1Tex;
	m_anim_param.split_all = 16;
	m_anim_param.split_width = 4;
	m_anim_param.split_height = 4;
}

PlayerBullet::~PlayerBullet()
{
}
