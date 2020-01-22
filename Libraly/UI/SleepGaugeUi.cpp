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
	m_pos.x = 1050.0f;
	m_pos.y = 30.0f;

	m_param.texture_id = GameCategoryTextureList::GameEnemySleepGauge;
	m_sleep_gauge = DataBank::Instance()->GetSleepGauge();

	sliders =
	{
		m_pos.x,							// X���W
		m_pos.y,							// Y���W
		0.0f,							// �ŏ��l
		100.0f,							// �ő�l
		m_sleep_gauge,				// ����̒l
		m_sleep_gauge,				// ���̒l
		0.0f,							// ���x 
		SliderDirection::LeftToRight,	// �i�s����
		m_param.category_id,
		m_param.texture_id				 // �g�p����e�N�X�`��
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
