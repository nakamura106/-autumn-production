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

	m_param.m_tex_id = GameCategoryTextureList::GameItemDropEffect;
}

void ItemDropEffect::Update()
{
}

void ItemDropEffect::Draw()
{
}
