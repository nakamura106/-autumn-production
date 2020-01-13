#include "SleepEffect.h"

SleepEffect::SleepEffect()
{
	Init();
}

SleepEffect::~SleepEffect()
{
}

void SleepEffect::Init()
{
	m_id = EffectID::SleepEffect;

	m_param.m_X = 0.0f;
	m_param.m_Y = 0.0f;
	m_param.m_offsetX = 0.0f;
	m_param.m_offsetY = 0.0f;
	m_param.IsLoop = true;
	m_param.m_tex_id = GameCategoryTextureList::GameSleepEffect;
}

void SleepEffect::Update()
{
}

void SleepEffect::Draw()
{
}
