#include "EffectBase.h"

EffectBase::EffectBase(ObjectBase* parent_)
{
	m_parent = parent_;
	Init();
}

EffectBase::~EffectBase()
{
}

void EffectBase::Init()
{
	m_effect_param.m_X = m_parent->GetPos().x + m_effect_param.m_offsetX;
	m_effect_param.m_Y = m_parent->GetPos().y + m_effect_param.m_offsetY;

	m_draw_param.category_id = TEXTURE_CATEGORY_GAME;
}

void EffectBase::Update()
{
	m_effect_param.m_X = m_parent->GetPos().x + m_effect_param.m_X;
	m_effect_param.m_Y = m_parent->GetPos().y + m_effect_param.m_Y;
}

void EffectBase::Draw()
{
	// �e�����o�ϐ��̒l�͔h���N���X���Ŏw�肷�邱��

	DrawUVTexture(
		m_effect_param.m_X,					//x���W
		m_effect_param.m_Y,					//y���W
		m_draw_param.tex_size_x,	//�e�N�X�`���̉��T�C�Y
		m_draw_param.tex_size_y,	//�e�N�X�`���̏c�T�C�Y
		GetTexture(m_draw_param.category_id, m_draw_param.texture_id),
		(m_draw_param.tu - 1.f) / (float)m_anime_param.split_width,
		(m_draw_param.tv - 1.f) / (float)m_anime_param.split_height);
}

void EffectBase::WakeUp()
{
	m_IsActive = true;
}

void EffectBase::Sleep()
{
	m_IsActive = false;
}

