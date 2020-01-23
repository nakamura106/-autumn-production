#include "EffectBase.h"

EffectBase::EffectBase(ObjectBase* parent_)
{
	m_parent = parent_;

	m_animation_timer = 0;
	m_is_animation_end = false;
	
	Init();
}

EffectBase::~EffectBase()
{
}

void EffectBase::Init()
{
	m_effect_param.m_X = m_parent->GetPos().x + m_effect_param.m_offsetX;
	m_effect_param.m_Y = m_parent->GetPos().y + m_effect_param.m_offsetY;

	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
}

void EffectBase::Update()
{
	if (m_IsActive == true)
	{
		m_effect_param.m_X = m_parent->GetPos().x + m_effect_param.m_offsetX;
		m_effect_param.m_Y = m_parent->GetPos().y + m_effect_param.m_offsetY;
	}

	AnimationUpdate();
}

void EffectBase::Draw()
{
	if (m_IsActive == true)
	{
		// 各メンバ変数の値は派生クラス内で指定すること

		DrawUVTexture(
			m_effect_param.m_X,					//x座標
			m_effect_param.m_Y,					//y座標
			m_draw_param.tex_size_x,	//テクスチャの横サイズ
			m_draw_param.tex_size_y,	//テクスチャの縦サイズ
			GetTexture(m_draw_param.category_id, m_draw_param.texture_id),
			(m_draw_param.tu - 1.f) / (float)m_anime_param.split_width,
			(m_draw_param.tv - 1.f) / (float)m_anime_param.split_height);

		// DrawTexture(m_effect_param.m_X, m_effect_param.m_Y, GetTexture(m_draw_param.category_id, m_draw_param.texture_id));
	}
	
}

void EffectBase::WakeUp()
{
	
	m_IsActive = true;
}

void EffectBase::Sleep()
{
	m_draw_param.tu = 1.0f;
	m_draw_param.tv = 1.0f;
	m_IsActive = false;
}

void EffectBase::AnimationUpdate()
{
	++m_animation_timer;

	m_is_animation_end = false;

	if (m_anime_param.split_all == 1)return;

	if (m_animation_timer >= m_anime_param.change_flame) {//画像を変更する

		m_animation_timer = 0;

		//横分割枚目を加算
		m_draw_param.tu += 1.f;

		//横分割枚目が画像の分割数以上の場合
		if (m_draw_param.tu > m_anime_param.split_width) {

			m_draw_param.tu = 1.f;

			//縦分割枚目を加算
			m_draw_param.tv += 1.f;

			//縦分割枚目が画像の分割数以上の場合
			if (m_draw_param.tv > m_anime_param.split_height) {

				m_draw_param.tv = 1.f;

			}
		}

		//tuとtvから計算した現在何枚目のアニメーションかが総枚数を超えていた場合、
		//tuとtvをリセット
		if (GetAnimationTexNum() > m_anime_param.split_all) {

			m_draw_param.tu = m_draw_param.tv = 1.f;

			//アニメーションの終わりであるフラグをオン
			m_is_animation_end = true;

		}

	}
}

int EffectBase::GetAnimationTexNum()
{
	return (((int)m_draw_param.tv - 1) * m_anime_param.split_width + (int)m_draw_param.tu);
}

