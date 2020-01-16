#include"SeaMap.h"
#include"../Map.h"
#include"../../Texture/Texture.h"
#include"../../Engine/Graphics.h"
#include"../../Engine/Input.h"
#include"../../DataBank/DataBank.h"
#include"../../Player/TrpPlayer.h"
#include"../../Manager/ObjectManager.h"


void SeaMap::Load()
{

	LoadTexture("Res/Tex/Map/�C/Sea2.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamefloorTex);	
	LoadTexture("Res/Tex/Map/�C/Sea3.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::Gamefloor2Tex);	
	LoadTexture("Res/Tex/Map/�C/Sea4.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBgTex);		


	
}

void SeaMap::Draw()
{
	DrawTexture(0.0f, 0.0f, GetTexture(TEXTURE_CATEGORY_GAME, GameBgTex));
	DrawTexture(floor2, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, Gamefloor2Tex));
	DrawTexture(floor1, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GamefloorTex));
}

void SeaFg::Load()
{
	LoadTexture("Res/Tex/Map/�C/Sea1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFgTex);	
}

void SeaFg::Draw()
{
	DrawTexture(fg, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameFgTex));
}