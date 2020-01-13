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

	m_param.m_X = 0.0f;
	m_param.m_Y = 0.0f;
	m_param.m_offsetX = 0.0f;
	m_param.m_offsetY = 0.0f;
	m_param.IsLoop = false;
	m_param.m_tex_id = GameCategoryTextureList::GameFailureEffect;
}

void FailureEffect::Update()
{
}

void FailureEffect::Draw()
{
}
