﻿#include "ObjectBase.h"
#include"../Manager/CollisionManager.h"
#include"../DataBank/DataBank.h"

const float G_OBJECT_DEFAULT_SPEED = 5.f;

ObjectBase::ObjectBase()
	:ObjectBase(ObjectRavel::Ravel_MapObj, Direction::RIGHT, G_OBJECT_DEFAULT_SPEED, 0)
{

}

ObjectBase::ObjectBase(ObjectRavel obj_ravel_, Direction direction_, float speed_, int draw_angle_)
{
	m_obj_ravel = obj_ravel_;
	m_direction = direction_;
	m_speed = speed_;
	m_is_delete = false;
	m_is_invincible = false;
	m_state = 0;
	m_animation_timer = 0;
	m_is_animation_end = false;
	m_hit_use_atk = 0.f;
	m_map_pos = 0.f;
	m_draw_angle = draw_angle_;
	m_draw_param.tu = 1.f;
	m_draw_param.tv = 1.f;
	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
	m_is_turn = false;
}

ObjectBase::ObjectBase(
	float pos_x_, 
	float pos_y_, 
	float size_x_,
	float size_y_,
	int tex_split_w_,
	int tex_split_h_,
	int tex_split_all,
	ObjectRavel obj_ravel_, 
	Direction direction_, 
	float speed_, 
	int draw_angle_,
	bool is_turn_
)
{
	m_pos.x					= pos_x_;
	m_map_pos				= pos_x_;
	m_pos.y					= pos_y_;
	m_obj_ravel				= obj_ravel_;
	m_direction				= direction_;
	m_speed					= speed_;
	m_draw_angle			= draw_angle_;
	m_is_turn				= is_turn_;
	m_draw_param.tex_size_x = size_x_;
	m_draw_param.tex_size_y = size_y_;
	m_anim_param.split_width = tex_split_w_;
	m_anim_param.split_height = tex_split_h_;
	m_anim_param.split_all = tex_split_all;

	m_is_delete				= false;
	m_is_invincible			= false;
	m_state					= 0;
	m_animation_timer		= 0;
	m_is_animation_end		= false;
	m_hit_use_atk			= 0.f;
	m_draw_param.tu			= 1.f;
	m_draw_param.tv			= 1.f;

	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Update()
{
	//CollisionManagerにオブジェクトを入れる
	CollisionManager::GetInstance().AddCollisionObject(this);

	//所持している有効なエフェクトのUpdateを呼ぶ
	for (int i = 0; i < static_cast<int>(m_effect_list.size()); ++i) {

		if (m_effect_list[i]->GetIsActive() == true)
		{
			m_effect_list[i]->Update();
		}
	}
}

void ObjectBase::Draw()
{
	// 各メンバ変数の値は派生クラス内で指定すること

	DrawUVTexture(
		m_pos.x,					//x座標
		m_pos.y,					//y座標
		m_draw_param.tex_size_x,	//テクスチャの横サイズ
		m_draw_param.tex_size_y,	//テクスチャの縦サイズ
		GetTexture(m_draw_param.category_id, m_draw_param.texture_id),
		(m_draw_param.tu - 1.f) / (float)m_anim_param.split_width,
		(m_draw_param.tv - 1.f) / (float)m_anim_param.split_height,
		m_draw_angle,
		m_is_turn
	);

	//エフェクトの描画
	for (int i = 0; i < static_cast<int>(m_effect_list.size()); ++i) {

		if (m_effect_list[i]->GetIsActive() == true)
		{
			m_effect_list[i]->Draw();
		}
	}
}

void ObjectBase::AnimationUpdate() 
{
	++m_animation_timer;
	
	m_is_animation_end = false;

	if (m_anim_param.split_all == 1)return;

	if (m_animation_timer >= m_anim_param.change_flame) {//画像を変更する

		m_animation_timer = 0;

		//横分割枚目を加算
		m_draw_param.tu += 1.f;

		//横分割枚目が画像の分割数以上の場合
		if (m_draw_param.tu > m_anim_param.split_width) {

			m_draw_param.tu = 1.f;

			//縦分割枚目を加算
			m_draw_param.tv += 1.f;

		}

		//tuとtvから計算した現在何枚目のアニメーションかが総枚数を超えていた場合、
		//tuとtvをリセット
		if (GetAnimationTexNum() > m_anim_param.split_all) {

			m_draw_param.tu = m_draw_param.tv = 1.f;

			//アニメーションの終わりであるフラグをオン
			m_is_animation_end = true;

		}

		//縦分割枚目が画像の分割数以上の場合
		if (m_draw_param.tv > m_anim_param.split_height) {

			m_draw_param.tv = 1.f;

		}

	}
}

int ObjectBase::GetAnimationTexNum()
{
	return (((int)m_draw_param.tv - 1) * m_anim_param.split_width + (int)m_draw_param.tu);
}


void ObjectBase::SetRectangle()
{
	m_rect_param.shift_x = 0.0f;
	m_rect_param.shift_y = 0.0f;
	m_rect_param.height = 0.0f;
	m_rect_param.width = 0.0f;
}

bool ObjectBase::CheckLandGround()
{
	return (m_pos.y + m_draw_param.tex_size_y) > G_GROUND_POS_Y;
}
 
void ObjectBase::CalcDrawPosition()
{
	//プレイヤーのワールド座標
	float p_map_pos = DataBank::Instance()->Getfloor1Pos();

	m_pos.x = m_map_pos + p_map_pos;

}

Position ObjectBase::GetPlayerCenter()
{
	if (DataBank::Instance()->GetPlayerdirection() == (int)Direction::RIGHT)
	{
		m_P_Center.x = m_pos.x + 80.0f;
		m_P_Center.y = m_pos.y + 128.0f;
	}
	if (DataBank::Instance()->GetPlayerdirection() == (int)Direction::LEFT)
	{
		m_P_Center.x = m_pos.x + 181.0f;
		m_P_Center.x = m_pos.y + 128.0f;
	}
	return m_P_Center;
}

Position ObjectBase::GetCenter(float texturesize_)
{
	m_Tex_Center.x = m_pos.x / texturesize_;
	m_Tex_Center.y = m_pos.y / texturesize_;
	return m_Tex_Center;
}

Position ObjectBase::GetCenter(float texturesizeX_, float texturesizeY_)
{
	m_Tex_Center.x = m_pos.x / texturesizeX_;
	m_Tex_Center.y = m_pos.y / texturesizeY_;
	return m_Tex_Center;
}