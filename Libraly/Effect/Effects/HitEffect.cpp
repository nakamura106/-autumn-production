#include "HitEffect.h"

HitEffect::HitEffect()
{
	Init();
}

HitEffect::~HitEffect()
{
}

void HitEffect::Init()
{
	m_id = EffectID::HitEffect;

	m_param.m_X = 0.0f;
	m_param.m_Y = 0.0f;
	m_param.m_offsetX = 0.0f;
	m_param.m_offsetY = 0.0f;
	m_param.IsLoop = false;
	m_param.m_tex_id = GameCategoryTextureList::GameHitEffect;
}

void HitEffect::Update()
{
}

void HitEffect::Draw()
{
}
