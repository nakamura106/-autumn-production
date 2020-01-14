#include "LandingEffect.h"

LandingEffect::LandingEffect()
{
	EffectBase::Init();
	Init();
}

LandingEffect::~LandingEffect()
{
}

void LandingEffect::Init()
{
	m_param.m_offsetX = 0.0f;
	m_param.m_offsetY = 0.0f;
	m_param.IsLoop = false;
	m_param.m_tex_id = GameCategoryTextureList::GameLandingEffect;
}

void LandingEffect::Update()
{
}

void LandingEffect::Draw()
{
}

EffectID LandingEffect::GetEffectID()
{
	return EffectID::LandingEffect;
}
