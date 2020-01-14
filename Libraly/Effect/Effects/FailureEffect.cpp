#include "FailureEffect.h"

FailureEffect::FailureEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

FailureEffect::~FailureEffect()
{
}

void FailureEffect::Init()
{
	m_effect_param.m_offsetX = 0.0f;
	m_effect_param.m_offsetY = 0.0f;
	m_effect_param.IsLoop = false;

	m_draw_param.texture_id = GameCategoryTextureList::GameFailureEffect;
	LoadTexture("Res/Tex/Effect/failure_E.png", m_draw_param.category_id, m_draw_param.texture_id);
}

void FailureEffect::Update()
{
}

EffectID FailureEffect::GetEffectID()
{
	return EffectID::FailureEffect;
}
