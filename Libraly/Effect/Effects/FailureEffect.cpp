#include "FailureEffect.h"
#include "../../DataBank/DataBank.h"

#define FAILURE_SIZE 64.0f
#define FAILURE_OFFX -60.0f
#define FAILURE_OFFY 0.0f

FailureEffect::FailureEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

FailureEffect::~FailureEffect()
{
}

void FailureEffect::Init()
{
	m_effect_param.m_offsetX = FAILURE_OFFX;
	m_effect_param.m_offsetY = FAILURE_OFFY;
	m_effect_param.IsLoop = false;

	m_draw_param.tex_size_x = FAILURE_SIZE;
	m_draw_param.tex_size_y = FAILURE_SIZE;

	m_anime_param.split_all = 4;
	m_anime_param.split_width = 2;
	m_anime_param.split_height = 2;
	m_anime_param.change_flame = 15;

	m_draw_param.texture_id = GameCategoryTextureList::GameFailureEffect;
	
}

void FailureEffect::Update()
{
	AnimationUpdate();
	if (m_IsActive == true)
	{
		if (DataBank::Instance()->GetPlayerdirection() == Direction::RIGHT)
		{
			m_effect_param.m_X = m_parent->GetPos().x + m_effect_param.m_offsetX;
			m_effect_param.m_Y = m_parent->GetPos().y + m_effect_param.m_offsetY;
		}
		else {
			m_effect_param.m_X = m_parent->GetPos().x + m_effect_param.m_offsetX + lrAdjustment;
			m_effect_param.m_Y = m_parent->GetPos().y + m_effect_param.m_offsetY;
		}
		
	}

	
}



EffectID FailureEffect::GetEffectID()
{
	return EffectID::FailureEffect;
}
