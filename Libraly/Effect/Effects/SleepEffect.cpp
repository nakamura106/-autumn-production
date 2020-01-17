#include "SleepEffect.h"

#define SLEEP_SIZE 128.0f
#define SLEEP_OFFX 0.0f
#define SLEEP_OFFY 170.0f


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
	m_effect_param.m_offsetX = SLEEP_OFFX;
	m_effect_param.m_offsetY = SLEEP_OFFY;
	m_effect_param.IsLoop = true;

	m_draw_param.tex_size_x = SLEEP_SIZE;
	m_draw_param.tex_size_y = SLEEP_SIZE;

	m_anime_param.split_all = 4;
	m_anime_param.split_width = 2;
	m_anime_param.split_height = 2;
	m_anime_param.change_flame = 15;

	m_draw_param.texture_id = GameCategoryTextureList::GameSleepEffect;
	
}


EffectID SleepEffect::GetEffectID()
{
	return EffectID::SleepEffect;
}
