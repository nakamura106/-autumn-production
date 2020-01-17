#include "DieEffect.h"

#define DIE_SIZE 128.0f
#define DIE_OFFX 0.0f
#define DIE_OFFY 170.0f

DieEffect::DieEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

DieEffect::~DieEffect()
{
}

void DieEffect::Init()
{
	m_effect_param.m_offsetX = DIE_OFFX;
	m_effect_param.m_offsetY = DIE_OFFY;
	m_effect_param.IsLoop = true;

	m_draw_param.tex_size_x = DIE_SIZE;
	m_draw_param.tex_size_y = DIE_SIZE;

	m_anime_param.split_all = 4;
	m_anime_param.split_width = 2;
	m_anime_param.split_height = 2;
	m_anime_param.change_flame = 15;

	m_draw_param.texture_id = GameCategoryTextureList::GameDieEffect;
	
}

EffectID DieEffect::GetEffectID()
{
	return EffectID::DieEffect;
}
