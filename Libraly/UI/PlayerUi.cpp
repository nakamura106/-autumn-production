#include "PlayerUi.h"


PlayerUi::PlayerUi()
{
	Init();
}

PlayerUi::~PlayerUi()
{
}

void PlayerUi::Init()
{
	m_pos.x = 20.0f;
	m_pos.y = 20.0f;
	LoadTexture("Res/Tex/Performance Symbol.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayerUi);
	m_param.category_id = TEXTURE_CATEGORY_GAME;
	m_param.texture_id = GameCategoryTextureList::GamePlayerUi;
}

void PlayerUi::Update()
{

}

void PlayerUi::Draw()
{
	// DrawTexture(0.0f, 0.0f, GetTexture(m_param.category_id, m_param.texture_id));
	DrawUVTexture(m_pos.x, m_pos.y, 524.0f, 222.0f, GetTexture(m_param.category_id, m_param.texture_id), 4096.0f, 256.0f);
}
