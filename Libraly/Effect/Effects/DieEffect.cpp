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

	m_param.m_X = 0.0f;
	m_param.m_Y = 0.0f;
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
