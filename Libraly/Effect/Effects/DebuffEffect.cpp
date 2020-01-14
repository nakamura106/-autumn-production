#include "DebuffEffect.h"

DebuffEffect::DebuffEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

DebuffEffect::~DebuffEffect()
{
}

void DebuffEffect::Init()
{
	// �I�t�Z�b�g�͌�Ŋm�F��ɐ������l�ɏC��
	m_effect_param.m_offsetX = 0.0f;
	m_effect_param.m_offsetY = 0.0f;
	m_effect_param.IsLoop = false;

	m_draw_param.texture_id = GameCategoryTextureList::GameDebuffEfect;
	LoadTexture("Res/Tex/Effect/debuff_E.png", m_draw_param.category_id, m_draw_param.texture_id);
}

void DebuffEffect::Update()
{
}

EffectID DebuffEffect::GetEffectID()
{
	return EffectID::DebuffEffect;
}
