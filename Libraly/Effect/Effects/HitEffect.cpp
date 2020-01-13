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

	m_param.m_tex_id = GameCategoryTextureList::GameHitEffect;
}

void HitEffect::Update()
{
}

void HitEffect::Draw()
{
}
