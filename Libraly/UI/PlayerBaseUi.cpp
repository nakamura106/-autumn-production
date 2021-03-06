#include "PlayerBaseUi.h"
#include "../DataBank/DataBank.h"
#include "../Object/Definition.h"


PlayerBaseUi::PlayerBaseUi()
{
	Init();
}

PlayerBaseUi::~PlayerBaseUi()
{
}

void PlayerBaseUi::Init()
{
	m_pos.x = PLAYERBASE_UI_POS_X;
	m_pos.y = PLAYERBASE_UI_POS_Y;
	

	m_param.texture_id = GameCategoryTextureList::GamePlayerUi;
	m_bullet_type = (int)PlayerBulletType::Default;
}

void PlayerBaseUi::Update()
{
	m_bullet_type = DataBank::Instance()->GetBulletType();
	if (m_bullet_type != (int)PlayerBulletType::Default)
	{
		ReleaseBulletType();
	}
}

void PlayerBaseUi::Draw()
{
	// DrawTexture(0.0f, 0.0f, GetTexture(m_param.category_id, m_param.texture_id));
	if (m_bullet_type == (int)PlayerBulletType::Chocho_1)
	{
		DrawUVTexture(m_pos.x, m_pos.y, 524.0f, 222.0f, GetTexture(m_param.category_id, m_param.texture_id), 0.12792969f * 1, 0);
	}
	else if (m_bullet_type == (int)PlayerBulletType::Chocho_2)
	{
		DrawUVTexture(m_pos.x, m_pos.y, 524.0f, 222.0f, GetTexture(m_param.category_id, m_param.texture_id), 0.12792969f * 4, 0);
	}
	else if (m_bullet_type == (int)PlayerBulletType::Tancho_1)
	{
		DrawUVTexture(m_pos.x, m_pos.y, 524.0f, 222.0f, GetTexture(m_param.category_id, m_param.texture_id), 0.12792969f * 3, 0);
	}
	else if (m_bullet_type == (int)PlayerBulletType::Tancho_2)
	{
		DrawUVTexture(m_pos.x, m_pos.y, 524.0f, 222.0f, GetTexture(m_param.category_id, m_param.texture_id), 0.12792969f * 0, 0);
	}
	else
	{
		DrawUVTexture(m_pos.x, m_pos.y, 524.0f, 222.0f, GetTexture(m_param.category_id, m_param.texture_id), 0.12792969f * 2, 0);
	}
	
}

void PlayerBaseUi::ReleaseBulletType()
{
	static int count = 0;
	count++;
	if (count >= 140)
	{
		DataBank::Instance()->SetBulletType((int)PlayerBulletType::Default);
		count = 0;
	}
}
