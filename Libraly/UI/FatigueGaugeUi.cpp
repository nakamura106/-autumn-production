#include "EnemyBaseUi.h"
#include "FatigueGaugeUi.h"



FatigueGaugeUi::FatigueGaugeUi()
{
	Init();
}

FatigueGaugeUi::~FatigueGaugeUi()
{
}

void FatigueGaugeUi::Init()
{
	LoadTexture("Res/Tex/EnemyUi/FatigueGauge.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemyFatigueGauge);
	LoadTexture("Res/Tex/EnemyUi/FatigueCircle.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemyFatigueCircle);
	LoadTexture("Res/Tex/EnemyUi/AutoHealGauge.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemyAutoHealGauge);
	m_pos.x = 1050.0f;
	m_pos.y = 30.0f;
	m_param.category_id = TEXTURE_CATEGORY_GAME;
	m_param.texture_id = GameCategoryTextureList::GameEnemyFatigueGauge;

	sliders =
	{
		m_pos.x,							// X座標
		m_pos.y,							// Y座標
		0.0f,							// 最小値
		100.0f,							// 最大値
		0.0f,							// 現状の値
		100.0f,							// 次の値
		0.0f,							// 速度 
		SliderDirection::LeftToRight,	// 進行方向
		m_param.category_id,
		m_param.texture_id				 // 使用するテクスチャ
	};

}

void FatigueGaugeUi::Update()
{
	static int count = 0;
	count++;
	
	UpdateSliderCurrentValue(sliders);

	if (count % 120 == 0)
	{
		UpdateSliderNextValue(sliders.MaxValue, sliders);
	}
	else if (count % 60 == 0)
	{
		UpdateSliderNextValue(sliders.MinValue, sliders);
	}

}

void FatigueGaugeUi::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, GameCategoryTextureList::GameEnemyAutoHealGauge));
	// DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, m_param.texture_id));
	DrawSliderUVMappingVersion(sliders);
}
