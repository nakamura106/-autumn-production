#include"Map.h"
#include"../Texture/Texture.h"
#include"../Engine/Graphics.h"



Map bg;		//�w�i
Map floor;	//��
Map fg;		//�ߌi
Map obj;	//�I�u�W�F�N�g

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
	LoadTexture("Res/Tex/�C �w�i.png",TEXTURE_CATEGORY_GAME,GameBgTex);
	LoadTexture("Res/Tex/�C �肷��.png", TEXTURE_CATEGORY_GAME, GamefloorTex);
	LoadTexture("Res/Tex/�C �l��.png", TEXTURE_CATEGORY_GAME, Gamefloor2Tex);

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