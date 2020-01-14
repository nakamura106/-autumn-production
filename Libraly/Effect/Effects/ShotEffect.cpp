#include "ShotEffect.h"

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
	m_effect_param.m_offsetX = 0.0f;
	m_effect_param.m_offsetY = 0.0f;
	m_effect_param.IsLoop = false;

	m_draw_param.texture_id = GameCategoryTextureList::GameShotEffect;
	LoadTexture("Res/Tex/Effect/shot_E.png", m_draw_param.category_id, m_draw_param.texture_id);
}

void ShotEffect::Update()
{
}

EffectID ShotEffect::GetEffectID()
{
	return EffectID::ShotEffect;
}
