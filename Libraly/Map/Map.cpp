#include"Map.h"
#include"../Texture/Texture.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include"../Player/TrpPlayer.h"
#include"../Manager/ObjectManager.h"





Map::Map()
{
	
}

Map::~Map()
{

}

void Map::Init()
{
	fg = 0;
	floor1 = 0;
	floor2 = 0;
	obj[0] = 400.0f;
	obj[1] = 1200.0f;
	obj[2] = 2000.f;
	m_speed = P_speed;
	m_pos.x = 0;
	m_pos.y = 0;
	
	Load();
}

void Map::Load()
{
	//マップ
	LoadTexture("Res/Tex/Map/森/Woods1.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameFgTex);		//草
	LoadTexture("Res/Tex/Map/森/Woods2.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GamefloorTex);	    //手すり
	LoadTexture("Res/Tex/Map/森/Woods3.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::Gamefloor2Tex);	//浜辺
	LoadTexture("Res/Tex/Map/森/Woods4.png",TEXTURE_CATEGORY_GAME,GameCategoryTextureList::GameBgTex);		    //海
	
	
	LoadTexture("Res/Tex/Map/森/Grass Small.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameObject);
	LoadTexture("Res/Tex/Map/森/Grass Medium.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameObject2);
	LoadTexture("Res/Tex/Map/森/Grass Large.png", TEXTURE_CATEGORY_GAME, GameCategoryTextureList::GameObject3);
}

void Map::Update()
{
	//右キーを押したときスクロール関数に右向き(スクロール方向)を送る
	if (GetKey(RIGHT_KEY) == true)
	{
		
		
			MapScroll(RIGHT);
		
	}
	//左キーを押したときスクロール関数に左向き(スクロール方向)を送る
	if (GetKey(LEFT_KEY) == true)
	{
		
		
		MapScroll(LEFT);
	}
	HitJudgement();
}

void Map::MapScroll(int direction_)
{
	//向きが右向きかつマップの端が-3800以上の時に右にスクロールする
	if (ObjectManager::Instance()->GetCharaObject((int)ObjectRavel::Ravel_Player)->GetPos().x <= Centerofscreen&& direction_==RIGHT && fg >= -3800.0f)
	{
		fg -= P_speed * 2;
		floor1 -= P_speed;
		obj[0] -= P_speed;
		obj[1] -= P_speed;
		obj[2] -= P_speed;
		floor2 -= floor2speed;
	}
	//向きが左向きかつマップの端が0以下の時に左にスクロールする
	if (direction_==LEFT&&fg< 0.0f)
	{
		fg += P_speed * 2;
		floor1 += P_speed;
		obj[0] += P_speed;
		obj[1] += P_speed;
		obj[2] += P_speed;
		floor2 += floor2speed;
	}
}

void Map::HitJudgement()
{
	
}

void Map::Draw()
{
	DrawTexture(0.0f, 0.0f, GetTexture(TEXTURE_CATEGORY_GAME, GameBgTex));
	DrawTexture(floor2, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, Gamefloor2Tex));
	DrawTexture(floor1, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GamefloorTex));
	DrawTexture(fg, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameFgTex));
	DrawTexture(obj[0], P_posYforest, GetTexture(TEXTURE_CATEGORY_GAME, GameObject));
	DrawTexture(obj[1], P_posYforest-100, GetTexture(TEXTURE_CATEGORY_GAME, GameObject2));
	DrawTexture(obj[2], P_posYforest-100, GetTexture(TEXTURE_CATEGORY_GAME, GameObject3));
}