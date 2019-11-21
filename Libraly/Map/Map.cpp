#include"Map.h"
#include"../Texture/Texture.h"
#include"../Engine/Graphics.h"
#include"../Player/TrpPlayer.h"



Map bg;		//îwåi
Map floor;	//è∞
Map floor2; //è∞2
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
	Load();
	Create();
}

void Map::Load()
{
	//LoadTexture("Res/Tex/Player_Taiki_Tp_Right.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamePlayer_Taiki_Tp_RightTex);



	LoadTexture("Res/Tex/äC îwåi.png",TEXTURE_CATEGORY_GAME,GameCategoryTextureList::GameBgTex);
	LoadTexture("Res/Tex/äC éËÇ∑ÇË.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamefloorTex);
	LoadTexture("Res/Tex/äC ïlï”.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::Gamefloor2Tex);
	LoadTexture("Res/Tex/äC ëê.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFgTex);
}

void Map::Create()
{	
	bg.m_pos.x = 0;
	bg.m_pos.y = 0;
	bg.m_speed = 0;
	floor.m_pos.x = 0;
	floor.m_pos.y = 0;
	floor.m_speed = 0;
	floor2.m_pos.x = 3480.0f;
	floor2.m_pos.y = 0;
	floor2.m_speed = 0;
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
	DrawTexture(floor.m_pos.x, floor.m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GamefloorTex));
	DrawTexture(floor2.m_pos.x, floor2.m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, Gamefloor2Tex));
	DrawTexture(fg.m_pos.x, fg.m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameFgTex));
	
}