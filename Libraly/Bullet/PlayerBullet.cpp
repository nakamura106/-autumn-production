#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(float x_, float y_, float move_speed_, Direction direction_, PlayerBulletType p_bullet_type_)
	:BulletBase(x_, y_, move_speed_, direction_)
{
	m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_1Tex;
	m_anim_param.split_all = 16;
	m_anim_param.split_width = 4;
	m_anim_param.split_height = 4;

	m_obj_ravel = ObjectRavel::Ravel_PlayerBullet;

	SetTextureID();

}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Load()
{
	//LoadTexture("Res/Tex/Effect/tyotyo01_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_1Tex);
}

void PlayerBullet::SetTextureID()
{
	switch (player_bullet_type)
	{
	case PlayerBulletType::Chocho_1:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_1Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet;
		break;

	case PlayerBulletType::Chocho_2:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_2Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet2;
		break;

	case PlayerBulletType::Tancho_1:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_3Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet3;
		break;

	case PlayerBulletType::Tancho_2:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_4Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet4;
		break;

	default:
		break;
	}
}

void PlayerBullet::HitAction(ObjectRavel ravel_, float hit_use_atk_)
{
	if (ravel_ == ObjectRavel::Ravel_Boss) {
		m_is_delete = true;
	}
}
