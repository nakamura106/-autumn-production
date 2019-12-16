#include "ObjectBase.h"
#include"../Manager/CollisionManager.h"
#include"../DataBank/DataBank.h"

ObjectBase::ObjectBase()
	:ObjectBase(ObjectRavel::Ravel_MapObj, Direction::RIGHT, 5.f)
{

}

ObjectBase::ObjectBase(ObjectRavel obj_ravel_, Direction direction_, float speed_)
{
	m_obj_ravel			= obj_ravel_;
	m_direction			= direction_;
	m_speed				= speed_;
	m_is_delete			= false;
	m_is_invincible		= false;
	m_state				= 0;
	m_animation_timer	= 0;
	m_animation_end		= false;
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Update()
{
	//CollisionManagerにオブジェクトを入れる
	CollisionManager::GetInstance().AddCollisionObject(this);
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
		(m_draw_param.tv - 1.f) / (float)m_anim_param.split_height
	);
}

void ObjectBase::AnimationUpdate() 
{
	++m_animation_timer;
	
	m_animation_end = false;

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

			//縦分割枚目が画像の分割数以上の場合
			if (m_draw_param.tv > m_anim_param.split_height) {

				m_draw_param.tv = 1.f;

			}
		}

		//tuとtvから計算した現在何枚目のアニメーションかが総枚数を超えていた場合、
		//tuとtvをリセット
		if (GetAnimationTexNum() > m_anim_param.split_all) {

			m_draw_param.tu = m_draw_param.tv = 1.f;

			//アニメーションの終わりであるフラグをオン
			m_animation_end = true;

		}

	}
}

int ObjectBase::GetAnimationTexNum()
{
	return (((int)m_draw_param.tv - 1) * m_anim_param.split_width + (int)m_draw_param.tu);
}

ObjectRavel ObjectBase::GetRavel()
{
	return m_obj_ravel;
}

HitRectangle ObjectBase::GetRectParam()
{
	return m_rect_param;
}



void ObjectBase::SetRectangle()
{
	m_rect_param.shift_x = 0.0f;
	m_rect_param.shift_y = 0.0f;
	m_rect_param.height = 0.0f;
	m_rect_param.width = 0.0f;
}
 
void ObjectBase::CalcDrawPosition()
{
	//プレイヤーのワールド座標
	float p_map_pos = DataBank::Instance()->Getfloor1Pos();

	//if (p_map_pos == 0.f)return;

	m_pos.x = m_map_pos + p_map_pos;

}
