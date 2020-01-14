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

EffectID FailureEffect::GetEffectID()
{
	return EffectID::FailureEffect;
}
