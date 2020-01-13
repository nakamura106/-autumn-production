#include "ItemDropEffect.h"

ItemDropEffect::ItemDropEffect()
{
	Init();
}

ItemDropEffect::~ItemDropEffect()
{
}

void ItemDropEffect::Init()
{
	m_id = EffectID::ItemDropEffect;

	m_param.m_X = 0.0f;
	m_param.m_Y = 0.0f;
	m_param.m_offsetX = 0.0f;
	m_param.m_offsetY = 0.0f;
	m_param.IsLoop = false;
	m_param.m_tex_id = GameCategoryTextureList::GameItemDropEffect;
}

void ItemDropEffect::Update()
{
}

void ItemDropEffect::Draw()
{
}
