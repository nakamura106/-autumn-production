#include"Map.h"
#include"../Texture/Texture.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../Player/TrpPlayer.h"



Map bg;		//îwåi
Map floor;	//è∞
Map floor2; //è∞2
Map fg;		//ãﬂåi
Map obj[3];	//ÉIÉuÉWÉFÉNÉg

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
	for (int i = 0; i < 3; i++)
	{
		obj[i].m_pos.x = 500.0f;
		obj[i].m_pos.y = P_posY;
		obj[i].m_speed = 0;
	}
	Load();
}

void Map::Load()
{
	LoadTexture("Res/Tex/äC îwåi.png",TEXTURE_CATEGORY_GAME,GameCategoryTextureList::GameBgTex);
	LoadTexture("Res/Tex/äC éËÇ∑ÇË.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamefloorTex);
	LoadTexture("Res/Tex/äC ïlï”.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::Gamefloor2Tex);
	LoadTexture("Res/Tex/äC ëê.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFgTex);
	LoadTexture("Res/Tex/ótè¨.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameObject);
	LoadTexture("Res/Tex/ótíÜ.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameObject2);
	LoadTexture("Res/Tex/ótëÂ.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameObject3);
}

void Map::Update()
{
	if (GetKey(RIGHT_KEY) == true)
	{
		if (fg.m_pos.x >= -3800.0f)
		{
			obj[0].m_pos.x = floor.m_pos.x -= P_speed;
			floor2.m_pos.x -= 3.0f;
			 fg.m_pos.x -= P_speed * 2;
		}
	}
	if (GetKey(LEFT_KEY) == true)
	{
		if (fg.m_pos.x < 0.0f)
		{
			obj[0].m_pos.x = floor.m_pos.x += P_speed;
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
	DrawTexture(obj[0].m_pos.x, obj[0].m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameObject));
	
}