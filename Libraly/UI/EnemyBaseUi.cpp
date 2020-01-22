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
	
	m_pos.x = ENEMYBASE_UI_POS_X;
	m_pos.y = ENEMYBASE_UI_POS_Y;
	m_param.texture_id = GameCategoryTextureList::GameEnemyUi2;
}

void EnemyBaseUi::Update()
{
	// Wave‚²‚Æ‚Ì
}