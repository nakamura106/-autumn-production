#include"Map.h"
#include"../Texture/Texture.h"
#include"../Engine/Graphics.h"
#include"../Engine/Input.h"
#include"../DataBank/DataBank.h"
#include"../Player/TrpPlayer.h"
#include"../Manager/ObjectManager.h"
#include"../Object/Definition.h"





Map::Map()
{

	m_obj_ravel = ObjectRavel::Ravel_Map;
	floor1 = 0;
	floor2 = 0;
	obj[0] = 400.0f;
	obj[1] = 1200.0f;
	obj[2] = 2000.f;
	m_speed = P_speed;
	m_pos.x = 0;
	m_pos.y = 0;
}

Map::~Map()
{

}

void Map::Init()
{
	

	
	Load();
}

void Map::Load()
{
	
}

void Map::Update()
{
	if (DataBank::Instance()->GetState() == (int)P_State::Move)
	{
		MapScroll();
	}
	
		
	DataBank::Instance()->Setfloor1Pos(floor1);
}

void Map::MapScroll()
{
	//向きが右向きかつマップの端が-3800以上の時に右にスクロールする
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x >= Centerofscreen&& DataBank::Instance()->GetfgPos()>=-3550.0f&&DataBank::Instance()->GetPlayerdirection()==RIGHT )
	{
		floor1 -= P_speed;
		obj[0] -= P_speed;
		obj[1] -= P_speed;
		obj[2] -= P_speed;
		floor2 -= floor2speed;
	}
	//向きが左向きかつマップの端が0以下の時に左にスクロールする
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x <= Centerofscreen&&DataBank::Instance()->GetfgPos()<0.0f&&floor1<0.0f&&floor2<0 && DataBank::Instance()->GetPlayerdirection() == LEFT)
	{
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
	DrawTexture(obj[0], P_posYforest, GetTexture(TEXTURE_CATEGORY_GAME, GameObject));
	DrawTexture(obj[1], P_posYforest - 100, GetTexture(TEXTURE_CATEGORY_GAME, GameObject2));
	DrawTexture(obj[2], P_posYforest - 100, GetTexture(TEXTURE_CATEGORY_GAME, GameObject3));
}


void Fg::Init()
{
	fg = 0;
	
	m_speed = P_speed;
	m_pos.x = 0;
	m_pos.y = 0;

	Load();
}

void Fg::Load()
{
	//マップ		

}

void Fg::Update()
{
	DataBank::Instance()->SetfgPos(fg);

	if (DataBank::Instance()->GetState() == (int)P_State::Move)
	{
		MapScroll();
	}
	
}

void Fg::MapScroll()
{
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x >= Centerofscreen && fg >= -3550.0f && DataBank::Instance()->GetPlayerdirection() == RIGHT)
	{
		fg -= P_speed * 2;
	}
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x <= Centerofscreen && fg < 0.0f && DataBank::Instance()->GetPlayerdirection() == LEFT)
	{
		fg += P_speed * 2;
	}
}

void Fg::Draw()
{
	DrawTexture(fg, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameFgTex));
}

