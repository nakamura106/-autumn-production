#include "ObjectBase.h"

ObjectBase::ObjectBase()
{
	/*注意‼　すべてのメンバの初期化は必須!!*/
	m_direction = Direction::RIGHT;
	m_is_delete = false;
	m_is_invincible = false;
	m_state = 0;
	m_speed = 0.f;

	m_animation_timer = 0;
}

ObjectBase::~ObjectBase()
{
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
		(m_draw_param.tu - 1) / m_anim_param.split_width,
		(m_draw_param.tv - 1) / m_anim_param.split_height
	);
}

void ObjectBase::AnimationUpdate() 
{
	++m_animation_timer;

	if (m_animation_timer >= m_anim_param.change_flame) {//画像を変更する

		m_animation_timer = 0;

		//横分割枚目を加算
		++m_draw_param.tu;

		//横分割枚目が画像の分割数以上の場合
		if (m_draw_param.tu > m_anim_param.split_width) {

			m_draw_param.tu = 1;

			//縦分割枚目を加算
			++m_draw_param.tv;

			//縦分割枚目が画像の分割数以上の場合
			if (m_draw_param.tv > m_anim_param.split_height) {

				m_draw_param.tv = 1;

			}
		}

		//tuとtvから計算した現在何枚目のアニメーションかが総枚数を超えていた場合、
		//tuとtvをリセット
		if (((m_draw_param.tv - 1) * m_anim_param.split_width + m_draw_param.tu) > m_anim_param.split_all) {

			m_draw_param.tu = m_draw_param.tv = 1;

		}

	}
}
 