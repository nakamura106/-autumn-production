#include"Map.h"
#include"../Texture/Texture.h"
#include"../Engine/Graphics.h"



Map bg;		//îwåi
Map floor;	//è∞
Map fg;		//ãﬂåi
Map obj;	//ÉIÉuÉWÉFÉNÉg

void Map::Init()
{
	bg.m_pos.x = 0;
	bg.m_pos.y = 0;
	bg.m_speed = 0;
	floor.m_pos.x = 0;
	floor.m_pos.y = 0;
	floor.m_speed = 0;
	fg.m_pos.x = 0;
	fg.m_pos.y = 0;
	fg.m_speed = 0;
	obj.m_pos.x = 0;
	obj.m_pos.y = 0;
	obj.m_speed = 0;
}

void Map::Load()
{
	LoadTexture("Res/Tex/äC îwåi.png",TEXTURE_CATEGORY_GAME,GameBgTex);
	LoadTexture("Res/Tex/äC éËÇ∑ÇË.png", TEXTURE_CATEGORY_GAME, GamefloorTex);
	LoadTexture("Res/Tex/äC ïlï”.png", TEXTURE_CATEGORY_GAME, Gamefloor2Tex);

}

void Map::Create()
{	
	bg.m_pos.x = 0;
	bg.m_pos.y = 0;
	bg.m_speed = 0;
	floor.m_pos.x = 0;
	floor.m_pos.y = 0;
	floor.m_speed = 0;
	fg.m_pos.x = 0;
	fg.m_pos.y = 0;
	fg.m_speed = 0;
	obj.m_pos.x = 0;
	obj.m_pos.y = 0;
	obj.m_speed = 0;
}

void Map::Update()
{

}

void Map::Draw()
{
	DrawTexture(bg.m_pos.x, bg.m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameBgTex));
}