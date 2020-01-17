#include "SweatEffect.h"

#define SWEAT_SIZE 64.0f
#define SWEAT_OFFX -80.0f
#define SWEAT_OFFY 15.0f 

SweatEffect::SweatEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	this->Init();
}

SweatEffect::~SweatEffect()
{
}

void SweatEffect::Init()
{
	m_effect_param.m_offsetX = SWEAT_OFFX;
	m_effect_param.m_offsetY = SWEAT_OFFY;
	m_effect_param.IsLoop = true;

	m_draw_param.tex_size_x = SWEAT_SIZE;
	m_draw_param.tex_size_y = SWEAT_SIZE;

	
	m_anime_param.split_all = 4;
	m_anime_param.split_width = 2;
	m_anime_param.split_height = 2;
	m_anime_param.change_flame = 15;

	m_draw_param.texture_id = GameCategoryTextureList::GameSweatEffect;
	
}


EffectID SweatEffect::GetEffectID()
{
	return EffectID::SweatEffect;
}
