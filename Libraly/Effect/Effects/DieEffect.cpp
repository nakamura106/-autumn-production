#include "DieEffect.h"

DieEffect::DieEffect()
{
	Init();
}

DieEffect::~DieEffect()
{
}

void DieEffect::Init()
{
	m_id = EffectID::DieEffect;

	m_param.m_tex_id = GameCategoryTextureList::GameDieEffect;
}

void DieEffect::Update()
{
}

void DieEffect::Draw()
{
}
