#include "HitEffect.h"

HitEffect::HitEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

HitEffect::~HitEffect()
{
}

void HitEffect::Init()
{
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

EffectID HitEffect::GetEffectID()
{
	return EffectID::HitEffect;
}
