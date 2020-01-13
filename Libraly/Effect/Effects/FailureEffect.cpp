#include "FailureEffect.h"

FailureEffect::FailureEffect()
{
	Init();
}

FailureEffect::~FailureEffect()
{
}

void FailureEffect::Init()
{
	m_id = EffectID::FailureEffect;

	m_param.m_tex_id = GameCategoryTextureList::GameFailureEffect;
}

void FailureEffect::Update()
{
}

void FailureEffect::Draw()
{
}
