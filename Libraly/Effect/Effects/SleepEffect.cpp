#include "SleepEffect.h"

SleepEffect::SleepEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

SleepEffect::~SleepEffect()
{
}

void SleepEffect::Init()
{
	m_effect_param.m_offsetX = 0.0f;
	m_effect_param.m_offsetY = 0.0f;
	m_effect_param.IsLoop = true;

	m_draw_param.texture_id = GameCategoryTextureList::GameSleepEffect;
	LoadTexture("Res/Tex/Effect/sleep_E.png", m_draw_param.category_id, m_draw_param.texture_id);
}

void SleepEffect::Update()
{
}

EffectID SleepEffect::GetEffectID()
{
	return EffectID::SleepEffect;
}
