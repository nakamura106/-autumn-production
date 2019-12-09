#include "EnemyAchieve.h"

EnemyAchieve::EnemyAchieve()
{
	Init();
}

EnemyAchieve::~EnemyAchieve()
{
}

void EnemyAchieve::Init()
{
	LoadTexture("Res/Tex/EnemyUi/EnemyAchieve.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameEnemyAchieveUi);
}

void EnemyAchieve::Update()
{
}

void EnemyAchieve::Draw()
{
}
