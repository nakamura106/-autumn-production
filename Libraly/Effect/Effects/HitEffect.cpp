#include "HitEffect.h"
#include "../../DataBank/DataBank.h"

HitEffect::HitEffect(ObjectBase* parent_):
	EffectBase(parent_)
{
	Init();
}

HitEffect::~HitEffect()
{
}

void HitEffect::Init()
{

	m_effect_param.m_offsetX = 0.0f;
	m_effect_param.m_offsetY = 0.0f;
	m_effect_param.IsLoop = false;

	m_draw_param.tex_size_x = 256.0f;
	m_draw_param.tex_size_y = 256.0f;

	m_anime_param.split_all = 10;
	m_anime_param.split_width = 4;
	m_anime_param.split_height = 2;
	m_anime_param.change_flame = 10;

	m_draw_param.texture_id = GameCategoryTextureList::GameHitEffect;
}

void HitEffect::Update()
{
	m_effect_param.m_X = DataBank::Instance()->GetBulletDeathPos().x;
	m_effect_param.m_Y = DataBank::Instance()->GetBulletDeathPos().y;

	AnimationUpdate();
	if (m_is_animation_end == true)
	{
		DataBank::Instance()->SetBulletDeathPosClear();
		m_IsActive = false;
	}
}


EffectID HitEffect::GetEffectID()
{
	return EffectID::HitEffect;
}
