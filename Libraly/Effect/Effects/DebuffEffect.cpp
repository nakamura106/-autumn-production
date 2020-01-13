#include "DebuffEffect.h"

DebuffEffect::DebuffEffect()
{
	Init();
}

DebuffEffect::~DebuffEffect()
{
}

void DebuffEffect::Init()
{
	m_id = EffectID::DebuffEffect;

	m_param.m_tex_id = GameCategoryTextureList::GameDebuffEfect;
}

void DebuffEffect::Update()
{
}

void DebuffEffect::Draw()
{
}
