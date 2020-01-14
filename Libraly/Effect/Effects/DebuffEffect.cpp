#include "DebuffEffect.h"

DebuffEffect::DebuffEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

DebuffEffect::~DebuffEffect()
{
}

void DebuffEffect::Init()
{
	// オフセットは後で確認後に正しい値に修正
	m_param.m_offsetX = 0.0f;
	m_param.m_offsetY = 0.0f;
	m_param.IsLoop = false;
	m_param.m_tex_id = GameCategoryTextureList::GameDebuffEfect;
}

void DebuffEffect::Update()
{
}

void DebuffEffect::Draw()
{
}

EffectID DebuffEffect::GetEffectID()
{
	return EffectID::DebuffEffect;
}
