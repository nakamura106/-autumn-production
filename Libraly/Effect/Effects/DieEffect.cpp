#include "DieEffect.h"

DieEffect::DieEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

DieEffect::~DieEffect()
{
}

void DieEffect::Init()
{
	m_param.m_offsetX = 0.0f;
	m_param.m_offsetY = 0.0f;
	m_param.IsLoop = true;
	m_param.m_tex_id = GameCategoryTextureList::GameDieEffect;
}

void DieEffect::Update()
{
}

void DieEffect::Draw()
{
}

EffectID DieEffect::GetEffectID()
{
	return EffectID::DieEffect;
}
