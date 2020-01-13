#include "DebuffEffect.h"

DebuffEffect::DebuffEffect()
{
	Init();
}

DebuffEffect::~DebuffEffect()
{
}

void DebuffEffect::Init()
{
	m_id = EffectID::DebuffEffect;

	// �L�����̍��W���ǂ������X,Y�ɑ������̂��H
	m_param.m_X = 0.0f;
	m_param.m_Y = 0.0f;
	// �I�t�Z�b�g�͌�Ŋm�F��ɐ������l�ɏC��
	m_param.m_offsetX = 0.0f;
	m_param.m_offsetY = 0.0f;
	m_param.IsLoop = false;
	m_param.m_tex_id = GameCategoryTextureList::GameDebuffEfect;
}

void DebuffEffect::Update()
{
}

void DebuffEffect::Draw()
{
}
