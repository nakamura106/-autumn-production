#include "PlayerBullet.h"
#include "../DataBank/DataBank.h"

PlayerBullet::PlayerBullet(float x_, float y_, float move_speed_, Direction direction_, PlayerBulletType p_bullet_type_)
	:BulletBase(x_, y_, move_speed_, direction_)
{
	m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_1Tex;
	m_anim_param.split_all = 16;
	m_anim_param.split_width = 4;
	m_anim_param.split_height = 4;

	m_obj_ravel = ObjectRavel::Ravel_PlayerBullet;

	player_bullet_type = p_bullet_type_;

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
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Chocho_1);	// UI用BulletType渡し関数
		break;

	case PlayerBulletType::Chocho_2:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_2Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet2;
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Chocho_2);
		break;

	case PlayerBulletType::Tancho_1:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_3Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet3;
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Tancho_1);
		break;

	case PlayerBulletType::Tancho_2:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_4Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet4;
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Tancho_2);
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

void PlayerBullet::Draw()
{
	DrawInversion(
		m_pos.x,					//x座標
		m_pos.y,					//y座標
		m_draw_param.tex_size_x,	//テクスチャの横サイズ
		m_draw_param.tex_size_y,	//テクスチャの縦サイズ		
		GetTexture(m_draw_param.category_id, m_draw_param.texture_id),
		(m_draw_param.tu - 1) / m_anim_param.split_width,
		(m_draw_param.tv - 1) / m_anim_param.split_height,
	m_direction);
}