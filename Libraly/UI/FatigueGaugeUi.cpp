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
		m_pos.x,							// X���W
		m_pos.y,							// Y���W
		0.0f,							// �ŏ��l
		100.0f,							// �ő�l
		m_fatigue_gauge,				// ����̒l
		m_fatigue_gauge,				// ���̒l
		0.0f,							// ���x 
		SliderDirection::LeftToRight,	// �i�s����
		m_param.category_id,
		m_param.texture_id				 // �g�p����e�N�X�`��
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
