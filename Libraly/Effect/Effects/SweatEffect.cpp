#include "SweatEffect.h"

SweatEffect::SweatEffect()
{
	Init();
}

SweatEffect::~SweatEffect()
{
}

void SweatEffect::Init()
{
	m_id = EffectID::SweatEffect;

	m_param.m_tex_id = GameCategoryTextureList::GameSweatEffect;
}

void SweatEffect::Update()
{
}

void SweatEffect::Draw()
{
}
