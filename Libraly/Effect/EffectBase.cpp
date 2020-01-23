#include "EffectBase.h"

EffectBase::EffectBase(ObjectBase* parent_)
{
	m_parent = parent_;

	m_animation_timer = 0;
	m_is_animation_end = false;
	
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
	if (m_IsActive == true)
	{
		m_effect_param.m_X = m_parent->GetPos().x + m_effect_param.m_offsetX;
		m_effect_param.m_Y = m_parent->GetPos().y + m_effect_param.m_offsetY;
	}

	AnimationUpdate();
}

void EffectBase::Draw()
{
	if (m_IsActive == true)
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

		// DrawTexture(m_effect_param.m_X, m_effect_param.m_Y, GetTexture(m_draw_param.category_id, m_draw_param.texture_id));
	}
	
}

void EffectBase::WakeUp()
{
	
	m_IsActive = true;
}

void EffectBase::Sleep()
{
	m_draw_param.tu = 1.0f;
	m_draw_param.tv = 1.0f;
	m_IsActive = false;
}

void EffectBase::AnimationUpdate()
{
	++m_animation_timer;

	m_is_animation_end = false;

	if (m_anime_param.split_all == 1)return;

	if (m_animation_timer >= m_anime_param.change_flame) {//�摜��ύX����

		m_animation_timer = 0;

		//���������ڂ����Z
		m_draw_param.tu += 1.f;

		//���������ڂ��摜�̕������ȏ�̏ꍇ
		if (m_draw_param.tu > m_anime_param.split_width) {

			m_draw_param.tu = 1.f;

			//�c�������ڂ����Z
			m_draw_param.tv += 1.f;

			//�c�������ڂ��摜�̕������ȏ�̏ꍇ
			if (m_draw_param.tv > m_anime_param.split_height) {

				m_draw_param.tv = 1.f;

			}
		}

		//tu��tv����v�Z�������݉����ڂ̃A�j���[�V���������������𒴂��Ă����ꍇ�A
		//tu��tv�����Z�b�g
		if (GetAnimationTexNum() > m_anime_param.split_all) {

			m_draw_param.tu = m_draw_param.tv = 1.f;

			//�A�j���[�V�����̏I���ł���t���O���I��
			m_is_animation_end = true;

		}

	}
}

int EffectBase::GetAnimationTexNum()
{
	return (((int)m_draw_param.tv - 1) * m_anime_param.split_width + (int)m_draw_param.tu);
}

