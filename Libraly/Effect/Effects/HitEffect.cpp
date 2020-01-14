#include "HitEffect.h"

HitEffect::HitEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

HitEffect::~HitEffect()
{
}

void HitEffect::Init()
{
	m_effect_param.m_offsetX = 0.0f;
	m_effect_param.m_offsetY = 0.0f;
	m_effect_param.IsLoop = false;

	m_draw_param.texture_id = GameCategoryTextureList::GameHitEffect;
	LoadTexture("Res/Tex/Effect/hit_E.png", m_draw_param.category_id, m_draw_param.texture_id);
}

void HitEffect::Update()
{
}

EffectID HitEffect::GetEffectID()
{
	return EffectID::HitEffect;
}
