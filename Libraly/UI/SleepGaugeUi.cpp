#include "SleepGaugeUi.h"

SleepGaugeUi::SleepGaugeUi()
{
	Init();
}

SleepGaugeUi::~SleepGaugeUi()
{
}

void SleepGaugeUi::Init()
{
	LoadTexture("Res/Tex/EnemyUi/SleepGauge.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemySleepGauge);
	LoadTexture("Res/Tex/EnemyUi/SleepCircle.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemySleepCircle);
	m_pos.x = 1050.0f;
	m_pos.y = 30.0f;
	m_param.category_id = TEXTURE_CATEGORY_GAME;
	m_param.texture_id = GameCategoryTextureList::GameEnemySleepGauge;
}

void SleepGaugeUi::Update()
{
}
