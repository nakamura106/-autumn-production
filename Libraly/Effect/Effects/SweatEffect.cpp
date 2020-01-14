#include "SweatEffect.h"

SweatEffect::SweatEffect()
{
	EffectBase::Init();
	Init();
}

SweatEffect::~SweatEffect()
{
}

void SweatEffect::Init()
{
	m_param.m_offsetX = 0.0f;
	m_param.m_offsetY = 0.0f;
	m_param.IsLoop = true;
	m_param.m_tex_id = GameCategoryTextureList::GameSweatEffect;
}

void SweatEffect::Update()
{
}

void SweatEffect::Draw()
{
}

EffectID SweatEffect::GetEffectID()
{
	return EffectID::SweatEffect;
}
