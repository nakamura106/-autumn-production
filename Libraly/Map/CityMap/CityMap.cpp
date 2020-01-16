#include"CityMap.h"
#include"../Map.h"
#include"../../Texture/Texture.h"
#include"../../Engine/Graphics.h"
#include"../../Engine/Input.h"
#include"../../DataBank/DataBank.h"
#include"../../Player/TrpPlayer.h"
#include"../../Manager/ObjectManager.h"


void CityMap::Load()
{

	LoadTexture("Res/Tex/Map/ŠX/Town2.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamefloorTex);	    //Stage1Bg2
	LoadTexture("Res/Tex/Map/ŠX/Town3.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::Gamefloor2Tex);	//Stage1Bg3
	LoadTexture("Res/Tex/Map/ŠX/Town4.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameBgTex);		    //Stage1Bg4

}

void CityMap::Draw()
{
	DrawTexture(0.0f, 0.0f, GetTexture(TEXTURE_CATEGORY_GAME, GameBgTex));
	DrawTexture(floor2, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, Gamefloor2Tex));
	DrawTexture(floor1, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GamefloorTex));
}

void CityFg::Load()
{
	LoadTexture("Res/Tex/Map/ŠX/Town1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFgTex);
}

void CityFg::Draw()
{
	DrawTexture(fg, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameFgTex));
}