#include "ShotEffect.h"

#define SHOT_SIZE 256.0f
#define SHOT_OFFX 0.0f
#define SHOT_OFFY -40.0f

ShotEffect::ShotEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

ShotEffect::~ShotEffect()
{
}

void ShotEffect::Init()
{
	m_effect_param.m_offsetX = SHOT_OFFX;
	m_effect_param.m_offsetY = SHOT_OFFY;
	m_effect_param.IsLoop = false;

	m_draw_param.tex_size_x = SHOT_SIZE;
	m_draw_param.tex_size_y = SHOT_SIZE;

	m_anime_param.split_all = 12;
	m_anime_param.split_width = 4;
	m_anime_param.split_height = 4;
	m_anime_param.change_flame = 15;

	m_draw_param.texture_id = GameCategoryTextureList::GameShotEffect;
	
}


EffectID ShotEffect::GetEffectID()
{
	return EffectID::ShotEffect;
}
