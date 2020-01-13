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

	m_param.m_X = 0.0f;
	m_param.m_Y = 0.0f;
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
