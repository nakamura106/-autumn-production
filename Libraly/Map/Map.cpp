#include"Map.h"
#include"../Texture/Texture.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../Player/TrpPlayer.h"



Map bg;		//”wŒi
Map floor;	//°
Map floor2; //°2
Map fg;		//‹ßŒi
Map obj;	//ƒIƒuƒWƒFƒNƒg

Map::Map()
{
	
}

Map::~Map()
{

}

void Map::Init()
{
	bg.m_pos.x = 0;
	bg.m_pos.y = 0;
	bg.m_speed = 0;
	floor.m_pos.x = 0;
	floor.m_pos.y = 0;
	floor.m_speed = 0;
	floor2.m_pos.x = 0.0f;
	floor2.m_pos.y = 0;
	floor2.m_speed = 0;
	fg.m_pos.x = 0;
	fg.m_pos.y = 0;
	fg.m_speed = 0;
	obj.m_pos.x = 0;
	obj.m_pos.y = 0;
	obj.m_speed = 0;
	Load();
}

void Map::Load()
{
	LoadTexture("Res/Tex/ŠC ”wŒi.png",TEXTURE_CATEGORY_GAME,GameCategoryTextureList::GameBgTex);
	LoadTexture("Res/Tex/ŠC Žè‚·‚è.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamefloorTex);
	LoadTexture("Res/Tex/ŠC •l•Ó.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::Gamefloor2Tex);
	LoadTexture("Res/Tex/ŠC ‘.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFgTex);
}

void Map::Update()
{
	if (GetKey(RIGHT_KEY) == true)
	{
		if (fg.m_pos.x >= -3800.0f)
		{
			floor.m_pos.x -= P_speed;
			floor2.m_pos.x -= 3.0f;
			fg.m_pos.x -= P_speed * 2;
		}
	}
	if (GetKey(LEFT_KEY) == true)
	{
		if (fg.m_pos.x < 0.0f)
		{
			floor.m_pos.x += P_speed;
			floor2.m_pos.x += 3.0f;
			fg.m_pos.x += P_speed * 2;
		}
	}
	
}

void Map::MapScroll()
{
	
}

void Map::Draw()
{
	
	DrawTexture(bg.m_pos.x, bg.m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameBgTex));
	DrawTexture(floor2.m_pos.x, floor2.m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, Gamefloor2Tex));
	DrawTexture(floor.m_pos.x, floor.m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GamefloorTex));
	DrawTexture(fg.m_pos.x, fg.m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameFgTex));
	
}