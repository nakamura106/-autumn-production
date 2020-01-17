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

	
}

void CityMap::Draw()
{
	DrawTexture(0.0f, 0.0f, GetTexture(TEXTURE_CATEGORY_GAME, GameBgTex));
	DrawTexture(floor2, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, Gamefloor2Tex));
	DrawTexture(floor1, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GamefloorTex));
}

void CityFg::Load()
{
	
}

void CityFg::Draw()
{
	DrawTexture(fg, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameFgTex));
}