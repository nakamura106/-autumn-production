#include "LandingEffect.h"

LandingEffect::LandingEffect()
{
	Init();
}

LandingEffect::~LandingEffect()
{
}

void LandingEffect::Init()
{
	m_id = EffectID::LandingEffect;

	m_param.m_tex_id = GameCategoryTextureList::GameLandingEffect;
}

void LandingEffect::Update()
{
}

void LandingEffect::Draw()
{
}
