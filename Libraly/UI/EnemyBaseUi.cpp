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
	m_param.texture_id = 0;
}

void EnemyBaseUi::Update()
{

}

void EnemyBaseUi::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, GameCategoryTextureList::GameEnemyUi2));
}
