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
}

void FatigueGaugeUi::Update()
{
}

void FatigueGaugeUi::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, GameCategoryTextureList::GameEnemyAutoHealGauge));
	// DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, m_param.texture_id));
}
