#include "ShotEffect.h"

ShotEffect::ShotEffect()
{
	Init();
}

ShotEffect::~ShotEffect()
{
}

void ShotEffect::Init()
{
	m_id = EffectID::ShotEffect;

	m_param.m_tex_id = GameCategoryTextureList::GameShotEffect;
}

void ShotEffect::Update()
{
}

void ShotEffect::Draw()
{
}
