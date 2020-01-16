#include"WoodsMap.h"
#include"../Map.h"
#include"../../Texture/Texture.h"
#include"../../Engine/Graphics.h"
#include"../../Engine/Input.h"
#include"../../DataBank/DataBank.h"
#include"../../Player/TrpPlayer.h"
#include"../../Manager/ObjectManager.h"


void WoodsMap::Load()
{

	LoadTexture("Res/Tex/Map/êX/Woods2.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamefloorTex);	  
	LoadTexture("Res/Tex/Map/êX/Woods3.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::Gamefloor2Tex);	
	LoadTexture("Res/Tex/Map/êX/Woods4.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBgTex);		

}

void WoodsMap::Draw()
{
	DrawTexture(0.0f, 0.0f, GetTexture(TEXTURE_CATEGORY_GAME, GameBgTex));
	DrawTexture(floor2, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, Gamefloor2Tex));
	DrawTexture(floor1, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GamefloorTex));
}

void WoodsFg::Load()
{
	LoadTexture("Res/Tex/Map/äC/Sea1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFgTex);
}

void WoodsFg::Draw()
{
	DrawTexture(fg, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameFgTex));
}