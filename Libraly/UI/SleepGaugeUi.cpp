#include "SleepGaugeUi.h"
#include "../DataBank/DataBank.h"

SleepGaugeUi::SleepGaugeUi()
{
	Init();
}

SleepGaugeUi::~SleepGaugeUi()
{
}

void SleepGaugeUi::Init()
{
	m_pos.x = SLEEPGAUGE_UI_POS_X;
	m_pos.y = SLEEPGAUGE_UI_POS_Y;

	m_param.texture_id = GameCategoryTextureList::GameEnemySleepGauge;
	m_sleep_gauge = DataBank::Instance()->GetSleepGauge();

	sliders =
	{
		m_pos.x,							// X座標
		m_pos.y,							// Y座標
		0.0f,							// 最小値
		100.0f,							// 最大値
		m_sleep_gauge,				// 現状の値
		m_sleep_gauge,				// 次の値
		0.0f,							// 速度 
		SliderDirection::LeftToRight,	// 進行方向
		m_param.category_id,
		m_param.texture_id				 // 使用するテクスチャ
	};

}

void SleepGaugeUi::Update()
{
	m_sleep_gauge = DataBank::Instance()->GetSleepGauge();


	UpdateSliderCurrentValue(sliders);
	UpdateSliderNextValue(m_sleep_gauge, sliders);
}

void SleepGaugeUi::Draw()
{
	DrawSliderUVMappingVersion(sliders);

	if (m_sleep_gauge >= 75.0f)
	{
		DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, GameCategoryTextureList::GameEnemySleepCircle));
	}
}
