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

	m_param.m_X = 0.0f;
	m_param.m_Y = 0.0f;
	m_param.m_offsetX = 0.0f;
	m_param.m_offsetY = 0.0f;
	m_param.IsLoop = false;
	m_param.m_tex_id = GameCategoryTextureList::GameShotEffect;
}

void ShotEffect::Update()
{
}

void ShotEffect::Draw()
{
}
