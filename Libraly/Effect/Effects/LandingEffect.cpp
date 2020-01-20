#include "LandingEffect.h"

#define LANDING_SIZE 128.0f
#define LANDING_OFFX -100.0f
#define LANDING_OFFY 140.0f
LandingEffect::LandingEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

LandingEffect::~LandingEffect()
{
}

void LandingEffect::Init()
{
	m_effect_param.m_offsetX = LANDING_OFFX;
	m_effect_param.m_offsetY = LANDING_OFFY;
	m_effect_param.IsLoop = false;

	m_draw_param.tex_size_x = LANDING_SIZE;
	m_draw_param.tex_size_y = LANDING_SIZE;

	m_anime_param.split_all = 3;
	m_anime_param.split_width = 2;
	m_anime_param.split_height = 2;
	m_anime_param.change_flame = 15;

	m_draw_param.texture_id = GameCategoryTextureList::GameLandingEffect;
	
}



EffectID LandingEffect::GetEffectID()
{
	return EffectID::LandingEffect;
}
