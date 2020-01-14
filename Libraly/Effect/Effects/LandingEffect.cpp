#include "LandingEffect.h"

LandingEffect::LandingEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

LandingEffect::~LandingEffect()
{
}

void LandingEffect::Init()
{
	m_effect_param.m_offsetX = 0.0f;
	m_effect_param.m_offsetY = 0.0f;
	m_effect_param.IsLoop = false;

	m_draw_param.texture_id = GameCategoryTextureList::GameLandingEffect;
	LoadTexture("Res/Tex/Effect/Landing_E.png", m_draw_param.category_id, m_draw_param.texture_id);
}

void LandingEffect::Update()
{
}

EffectID LandingEffect::GetEffectID()
{
	return EffectID::LandingEffect;
}
