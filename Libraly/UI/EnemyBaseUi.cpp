#include "EnemyBaseUi.h"

EnemyBaseUi::EnemyBaseUi()
{
	Init();
}

EnemyBaseUi::~EnemyBaseUi()
{

}

void EnemyBaseUi::Init()
{
	
	m_pos.x = 1050.0f;
	m_pos.y = 30.0f;
	m_param.category_id = TEXTURE_CATEGORY_GAME;
	m_param.texture_id = GameCategoryTextureList::GameEnemyUi2;
	m_gauge_base_texid = GameCategoryTextureList::GameEnemyGaugeBase;
}

void EnemyBaseUi::Update()
{

}

void EnemyBaseUi::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, m_gauge_base_texid));
	DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, m_param.texture_id));
}
