#include "PlayerBulletUi.h"

PlayerBulletUi::PlayerBulletUi()
{
	Init();
}

PlayerBulletUi::~PlayerBulletUi()
{

}

void PlayerBulletUi::Init()
{
	LoadTexture("Res/Tex/Chabon Melody/Blue_Center.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_BlueCenter);
	LoadTexture("Res/Tex/Chabon Melody/Blue_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_BlueLeft);
	LoadTexture("Res/Tex/Chabon Melody/Blue_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_BlueRight);
	LoadTexture("Res/Tex/Chabon Melody/Green_Center.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_GreenCenter);
	LoadTexture("Res/Tex/Chabon Melody/Pink_Center.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_PinkCenter);
	LoadTexture("Res/Tex/Chabon Melody/Purple_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_PurpleRight);
	LoadTexture("Res/Tex/Chabon Melody/Red_Center.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_RedCenter);
	LoadTexture("Res/Tex/Chabon Melody/Red_Left.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_RedLeft);
	LoadTexture("Res/Tex/Chabon Melody/Red_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_RedRight);
	LoadTexture("Res/Tex/Chabon Melody/Yellow_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBulletUi_YellowRight);

	m_pos.x = 20.0f;
	m_pos.y = 20.0f;
	m_param.category_id = TEXTURE_CATEGORY_GAME;
	m_param.texture_id = GameCategoryTextureList::GameBulletUi_RedLeft;

}

void PlayerBulletUi::Update()
{
}

