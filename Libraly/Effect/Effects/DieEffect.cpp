#include "DieEffect.h"

DieEffect::DieEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

DieEffect::~DieEffect()
{
}

void DieEffect::Init()
{
	m_effect_param.m_offsetX = 0.0f;
	m_effect_param.m_offsetY = 0.0f;
	m_effect_param.IsLoop = true;

	m_draw_param.texture_id = GameCategoryTextureList::GameDieEffect;
	LoadTexture("Res/Tex/Effect/die_E.png", m_draw_param.category_id, m_draw_param.texture_id);
}

void DieEffect::Update()
{
}

EffectID DieEffect::GetEffectID()
{
	return EffectID::DieEffect;
}
