#include "PlayerHpUi.h"

PlayerHpUi::PlayerHpUi()
{
	Init();
}

PlayerHpUi::~PlayerHpUi()
{
}

void PlayerHpUi::Init()
{
	LoadTexture("Res/Tex/Life/HP0.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerHp_0Tex);
	LoadTexture("Res/Tex/Life/HP1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerHp_1Tex);
	LoadTexture("Res/Tex/Life/HP2.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerHp_2Tex);
	LoadTexture("Res/Tex/Life/HP3.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerHp_3Tex);

	m_pos.x = 20.0f;
	m_pos.y = 20.0f;
	m_param.category_id = TEXTURE_CATEGORY_GAME;
	m_param.texture_id = GameCategoryTextureList::GamePlayerHp_3Tex;

}

void PlayerHpUi::Update()
{
}

void PlayerHpUi::Draw()
{
	DrawTexture(m_pos.x, m_pos.y, GetTexture(m_param.category_id, m_param.texture_id));
}
