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
	
	m_speed = P_speed;
	m_pos.x = 0;
	m_pos.y = 0;
	
}

Map::~Map()
{

}

void Map::Init()
{
	

	
	
}



void Map::Update()
{

	if ((IsButtonPush(LeftButton)||GetKey(LEFT_KEY) == true)&&DataBank::Instance()->GetWavetype(WaveType::Wave1)==false && DataBank::Instance()->GetWavetype(WaveType::Wave2) == false && DataBank::Instance()->GetWavetype(WaveType::Wave3) == false)
	{
		MapScroll(LEFT);
	}
	if ((IsButtonPush(RightButton) || GetKey(RIGHT_KEY) == true) && DataBank::Instance()->GetWavetype(WaveType::Wave1) == false && DataBank::Instance()->GetWavetype(WaveType::Wave2) == false && DataBank::Instance()->GetWavetype(WaveType::Wave3) == false)
	{
		MapScroll(RIGHT);
	}

		
	DataBank::Instance()->Setfloor1Pos(floor1);
}

void Map::MapScroll(int direction_)
{
	//向きが右向きかつマップの端が-3800以上の時に右にスクロールする
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x >= Centerofscreen&& DataBank::Instance()->GetfgPos()>=-3550.0f&&direction_==RIGHT )
	{
		floor1 -= P_speed;
		
		floor2 -= floor2speed;
	}
	//向きが左向きかつマップの端が0以下の時に左にスクロールする
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x <= Centerofscreen&&DataBank::Instance()->GetfgPos()<0.0f&&floor1<0.0f&&floor2<0 && direction_ == LEFT)
	{
		floor1 += P_speed;
	
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

	if ((IsButtonPush(LeftButton) || GetKey(RIGHT_KEY) == true) && DataBank::Instance()->GetWavetype(WaveType::Wave1) == false && DataBank::Instance()->GetWavetype(WaveType::Wave2) == false && DataBank::Instance()->GetWavetype(WaveType::Wave3) == false)
	{
		MapScroll(LEFT);
	}
	if ((IsButtonPush(RightButton) || GetKey(RIGHT_KEY) == true) && DataBank::Instance()->GetWavetype(WaveType::Wave1) == false && DataBank::Instance()->GetWavetype(WaveType::Wave2) == false && DataBank::Instance()->GetWavetype(WaveType::Wave3) == false)
	{
		MapScroll(RIGHT);
	}
	
}

void Fg::MapScroll(int direction_)
{
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x >= Centerofscreen && fg >= -3550.0f && direction_ == RIGHT)
	{
		fg -= P_speed * 2;
	}
	if (ObjectManager::Instance()->GetCharaObject(ObjectRavel::Ravel_Player)->GetPos().x <= Centerofscreen && fg < 0.0f && direction_ == LEFT)
	{
		fg += P_speed * 2;
	}
	
}

void  Fg::WaveChange(float enemyX_)
{
	if (enemyX_ >= 960.0f)
	{
		fg += P_speed * 4;
	}
	else
	{
		for (int i = 0; i < (int)WaveType::WaveMax; i++)
		{
			DataBank::Instance()->SetWave((WaveType)i, false);
		}
	}
	if (enemyX_ <= 960.0f)
	{
		fg -= P_speed * 4;
	}
	else
	{
		for (int i = 0; i < (int)WaveType::WaveMax; i++)
		{
			DataBank::Instance()->SetWave((WaveType)i, false);
		}
	}
}

void Fg::Draw()
{
	DrawTexture(fg, m_pos.y, GetTexture(TEXTURE_CATEGORY_GAME, GameFgTex));
}

