#include "PlayerBullet.h"
#include "../DataBank/DataBank.h"

PlayerBullet::PlayerBullet(float x_, float y_, float move_speed_, Direction direction_, PlayerBulletType p_bullet_type_)
	:BulletBase(x_, y_, move_speed_, direction_,ObjectRavel::Ravel_PlayerBullet)
{
	m_draw_param.texture_id		= GameCategoryTextureList::GamePlayerBullet_1Tex;
	m_anim_param.split_all		= M_PBULLET_ANIM_SPLIT_ALL;
	m_anim_param.split_width	= M_PBULLET_ANIM_SPLIT_W;
	m_anim_param.split_height	= M_PBULLET_ANIM_SPLIT_H;
	player_bullet_type			= p_bullet_type_;

	//プレイヤーの弾の情報を格納
	SetPlayerBulletInfo();

	m_upward_thrust = 25.0f;

}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Load()
{
	//LoadTexture("Res/Tex/Effect/tyotyo01_E.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerBullet_1Tex);
}

void PlayerBullet::SetPlayerBulletInfo()
{
	switch (player_bullet_type)
	{
	case PlayerBulletType::Chocho_1:
		//使用するテクスチャを設定
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_1Tex;

		//オブジェクトの種類(ラベル)設定
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet;

		// UI用BulletType渡し関数
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Chocho_1);

		//この弾が持つ当たり判定時の情報を設定
		m_hit_use_atk = M_CHOCHO_1_NUM;

		break;

	case PlayerBulletType::Chocho_2:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_2Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet2;
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Chocho_2);
		m_hit_use_atk = M_CHOCHO_2_NUM;
		break;

	case PlayerBulletType::Tancho_1:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_3Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet3;
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Tancho_1);
		m_hit_use_atk = M_TANCHO_1_NUM;
		break;

	case PlayerBulletType::Tancho_2:
		m_draw_param.texture_id = GameCategoryTextureList::GamePlayerBullet_4Tex;
		m_obj_ravel = ObjectRavel::Ravel_PlayerBullet4;
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Tancho_2);
		m_hit_use_atk = M_TANCHO_2_NUM;
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

void PlayerBullet::Update()
{
	BulletBase::Update();

	CalcDrawPosition();

	AnimationUpdate();
}

void PlayerBullet::MoveUpdate()
{
	switch (DataBank::Instance()->GetPlayerType())
	{
	case (int)Player::PlayerTypeTrumpet:
		BulletBase::MoveUpdate();
		break;
	case (int)Player::PlayerTypeFlute:
		MoveFluteUpdate();
		break;
	case (int)Player::PlayerTypeTuba:
		MoveTubaUpdate();
		break;
	default:
		break;
	}
}

void PlayerBullet::MoveFluteUpdate()
{



}

void PlayerBullet::MoveTubaUpdate()
{
	m_pos.y -= m_upward_thrust;
	m_upward_thrust -= 0.6f;
	if (m_direction == Direction::RIGHT) {
		m_map_pos += m_speed*1.3f;
	}
	else if (m_direction == Direction::LEFT) {
		m_map_pos -= m_speed*1.3f;
	}
	
	if (m_pos.y >= 900.0f)
	{
		m_is_delete = true;
		m_upward_thrust = 25.0f;
	}

}