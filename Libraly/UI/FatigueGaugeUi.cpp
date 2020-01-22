#include "EnemyBaseUi.h"
#include "FatigueGaugeUi.h"
#include "../DataBank/DataBank.h"



FatigueGaugeUi::FatigueGaugeUi()
{
	Init();
}

FatigueGaugeUi::~FatigueGaugeUi()
{
}

void FatigueGaugeUi::Init()
{
	
	m_pos.x = 1050.0f;
	m_pos.y = 30.0f;
	m_param.texture_id = GameCategoryTextureList::GameEnemyFatigueGauge;
	m_fatigue_gauge = DataBank::Instance()->GetFatigueGauge();
	
	sliders =
	{
		m_pos.x,							// X座標
		m_pos.y,							// Y座標
		0.0f,							// 最小値
		100.0f,							// 最大値
		m_fatigue_gauge,				// 現状の値
		m_fatigue_gauge,				// 次の値
		0.0f,							// 速度 
		SliderDirection::LeftToRight,	// 進行方向
		m_param.category_id,
		m_param.texture_id				 // 使用するテクスチャ
	};

}

void FatigueGaugeUi::Update()
{
	m_fatigue_gauge = DataBank::Instance()->GetFatigueGauge();
	
	
	UpdateSliderCurrentValue(sliders);
	UpdateSliderNextValue(m_fatigue_gauge, sliders);

}

void FatigueGaugeUi::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, GameCategoryTextureList::GameEnemyGaugeBase));

	DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, GameCategoryTextureList::GameEnemyAutoHealGauge));

	DrawSliderUVMappingVersion(sliders);

	if (m_fatigue_gauge >= 100.0f)
	{
		DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, GameCategoryTextureList::GameEnemyFatigueCircle));
	}
}
