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
	m_pos.x = ACHIEVE_POS_X;
	m_pos.y = ACHIEVE_POS_Y;
	m_param.category_id = TEXTURE_CATEGORY_GAME;
	m_param.texture_id = GameCategoryTextureList::GameEnemyAchieveUi;
	m_animation_state = 1;
}

void EnemyAchieve::Update()
{
	static int count = 0;
	count++;

	if (count >= 25)
	{
		m_animation_state++;
		if (m_animation_state >= 4)
		{
			m_animation_state = 1;
		}
		count = 0;
	}

}

void EnemyAchieve::Draw()
{
	// ÉTÉCÉY130*130
	DrawUVTexture(m_pos.x, m_pos.y, 130.0f, 130.0f, GetTexture(m_param.category_id, m_param.texture_id), 0.12695312f * m_animation_state, 0);
}
