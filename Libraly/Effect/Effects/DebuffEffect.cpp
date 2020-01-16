#include "DebuffEffect.h"

#define DEBUFF_SIZE 256.0f
#define DEBUFF_OFFX -60.0f
#define DEBUFF_OFFY 0.0f

DebuffEffect::DebuffEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

DebuffEffect::~DebuffEffect()
{
}

void DebuffEffect::Init()
{
	// オフセットは後で確認後に正しい値に修正
	m_effect_param.m_offsetX = DEBUFF_OFFX;
	m_effect_param.m_offsetY = DEBUFF_OFFY;
	m_effect_param.IsLoop = false;

	m_draw_param.tex_size_x = DEBUFF_SIZE;
	m_draw_param.tex_size_y = DEBUFF_SIZE;

	m_anime_param.split_all = 3;
	m_anime_param.split_width = 2;
	m_anime_param.split_height = 2;
	m_anime_param.change_flame = 15;

	m_draw_param.texture_id = GameCategoryTextureList::GameDebuffEfect;
	LoadTexture("Res/Tex/Effect/debuff_E.png", m_draw_param.category_id, m_draw_param.texture_id);
}



EffectID DebuffEffect::GetEffectID()
{
	return EffectID::DebuffEffect;
}
