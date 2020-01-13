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

	m_param.m_tex_id = GameCategoryTextureList::GameSleepEffect;
}

void SleepEffect::Update()
{
}

void SleepEffect::Draw()
{
}
