#include "PlayerHpUi.h"
#include "../Object/Definition.h"
#include "../DataBank/DataBank.h"


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
	m_hp_state = PlayerHpState::Hp3;

}

void PlayerHpUi::Update()
{
	switch (DataBank::Instance()->GetPlayerHp())
	{
	case 4:
		m_hp_state = PlayerHpState::Hp4;
		break;
	case 3:
		m_hp_state = PlayerHpState::Hp3;
		break;
	case 2:
		m_hp_state = PlayerHpState::Hp2;
		break;
	case 1:
		m_hp_state = PlayerHpState::Hp1;
		break;
	case 0:
		m_hp_state = PlayerHpState::Hp0;
		break;
	}

	GetPlayerHpState();

	switch(m_hp_state)
	{
	case PlayerHpState::Hp4:
		m_param.texture_id = GameCategoryTextureList::GamePlayerHp_0Tex; // ‚É‚·‚é
	case PlayerHpState::Hp3:
		m_param.texture_id = GameCategoryTextureList::GamePlayerHp_3Tex;
		break;
	case PlayerHpState::Hp2:
		m_param.texture_id = GameCategoryTextureList::GamePlayerHp_2Tex;
		break;
	case PlayerHpState::Hp1:
		m_param.texture_id = GameCategoryTextureList::GamePlayerHp_1Tex;
		break;
	case PlayerHpState::Hp0:
		m_param.texture_id = GameCategoryTextureList::GamePlayerHp_0Tex;
		break;
	}

}

void PlayerHpUi::GetPlayerHpState()
{
	int pHp = 3;	// ‰¼•Ï”@–{—ˆ‚Íplayerobj‚©‚ç”’l‚ğæ“¾‚·‚é

	switch (pHp)
	{
	case 3:
		m_hp_state = Hp3;
		break;
	case 2:
		m_hp_state = Hp2;
		break;
	case 1:
		m_hp_state = Hp1;
		break;
	case 0:
		m_hp_state = Hp0;
		break;
	default:
		break;
	}
}


