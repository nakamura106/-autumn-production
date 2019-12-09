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
	LoadTexture("Res/Tex/EnemyUi/LifeBaseBar.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemyUi);
	m_pos.x = 1050.0f;
	m_pos.y = 30.0f;
	m_param.category_id = TEXTURE_CATEGORY_GAME;
	m_param.texture_id = GameCategoryTextureList::GameEnemyUi;
}

void EnemyBaseUi::Update()
{

}
