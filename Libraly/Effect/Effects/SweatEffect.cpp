#include "SweatEffect.h"

SweatEffect::SweatEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	this->Init();
}

SweatEffect::~SweatEffect()
{
}

void SweatEffect::Init()
{
	m_effect_param.m_offsetX = 0.0f;
	m_effect_param.m_offsetY = 0.0f;
	m_effect_param.IsLoop = true;

	m_draw_param.texture_id = GameCategoryTextureList::GameSweatEffect;
	LoadTexture("Res/Tex/Effect/sweat_E.png", m_draw_param.category_id, m_draw_param.texture_id);
}


EffectID SweatEffect::GetEffectID()
{
	return EffectID::SweatEffect;
}
