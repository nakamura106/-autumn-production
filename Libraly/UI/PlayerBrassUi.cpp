#include "PlayerBrassUi.h"
#include "../DataBank/DataBank.h"

PlayerBrassUi::PlayerBrassUi()
{
	Init();
}

PlayerBrassUi::~PlayerBrassUi()
{
}

void PlayerBrassUi::Init()
{
	m_pos.x = BRASSUI_POS_X;
	m_pos.y = BRASSUI_POS_Y;
	
	if (DataBank::Instance()->GetPlayerType() == static_cast<int>(Player::PlayerTypeTrumpet))
	{
		m_param.texture_id = GameCategoryTextureList::GamePlayerBrassUi1;
	}
	else if (DataBank::Instance()->GetPlayerType() == static_cast<int>(Player::PlayerTypeFlute))
	{
		m_param.texture_id = GameCategoryTextureList::GamePlayerBrassUi2;
	}
	else if (DataBank::Instance()->GetPlayerType() == static_cast<int>(Player::PlayerTypeTuba))
	{
		m_param.texture_id = GameCategoryTextureList::GamePlayerBrassUi3;
	}
}

void PlayerBrassUi::Update()
{
}
