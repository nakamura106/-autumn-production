#include "ObjectManager.h"
#include "../Player/TrpPlayer.h"
#include"../Player/FlutePlayer/FlutePlayer.h"
#include"../Player/TubaPlayer/TubaPlayer.h"
#include "../Map/Map.h"
#include"../Map/WoodsMap/WoodsMap.h"
#include"../Map/SeaMap/SeaMap.h"
#include"../Map/CityMap/CityMap.h"
#include "../Enemy/Mouse.h"
#include"../Enemy/Bird.h"
#include"../Enemy/Gorilla.h"
#include"CollisionManager.h"
#include"../DataBank/DataBank.h"
#include"../Object/MapObject/BananaObject.h"
#include"../Object/MapObject/FountainObject.h"
#include"../Object/MapObject/GrassObject.h"
#include"../Object/MapObject/LargeGrassObject.h"
#include"../Object/MapObject/SmallGrassObject.h"


ObjectManager* ObjectManager::p_instance = 0;

ObjectManager* ObjectManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new ObjectManager;
	}

	return  p_instance;
}

ObjectBase* ObjectManager::GetCharaObject(ObjectRavel ravel_)
{
	for (int i = 0;i < MAX_CHARA_OBJ;++i) {

		if (chara_objects[i]->GetRavel() == ravel_) {

			return chara_objects[i];

		}
	}
	
	return nullptr;
}

ObjectManager::ObjectManager()
{
	for (int i = 0; i < MAX_CHARA_OBJ; i++)
	{
		if (chara_objects[i] != nullptr)
		{
			chara_objects[i] = nullptr;
		}
	}
}

ObjectManager::~ObjectManager()
{
	for (int i = 0; i < MAX_CHARA_OBJ; i++)
	{
		if (chara_objects[i] != nullptr)
		{
			delete chara_objects[i];
			chara_objects[i] = nullptr;
		}
	}
}

void ObjectManager::AllDaleteObject()
{
	for (int i = 0; i < MAX_CHARA_OBJ; i++)
	{
		if (chara_objects[i] != nullptr)
		{
			delete chara_objects[i];
			chara_objects[i] = nullptr;
		}
	}
}

// ポインタ配列の中身にすべてNULLを入れておく
void ObjectManager::Init()
{
	for (int i = 0; i < MAX_CHARA_OBJ; i++)
	{
		if (chara_objects[i] != nullptr)
		{
			chara_objects[i]->Init();
		}
	}
}

void ObjectManager::CreateObject()
{
	switch (DataBank::Instance()->GetMapType())
	{
	case (int)MapType::WoodsMap:
		chara_objects[0] = new WoodsMap;
		chara_objects[1] = new SmallGrassObject;
		chara_objects[2] = new GrassObject;
		chara_objects[3] = new LargeGrassObject;
		chara_objects[4] = new HedgeHog;
		chara_objects[6] = new WoodsFg;
		break;
	case (int)MapType::SeaMap:
		chara_objects[0] = new SeaMap;
		chara_objects[1] = new Bird;
		chara_objects[3] = new SeaFg;
		break;
	case (int)MapType::CityMap:
		chara_objects[0] = new CityMap;
		chara_objects[1] = new BananaObject;
		chara_objects[2] = new FountainObject;
		chara_objects[3] = new Gorilla;
		chara_objects[5] = new CityFg;
		break;
	default:
		chara_objects[0] = new WoodsMap;
		chara_objects[2] = new HedgeHog;
		chara_objects[4] = new WoodsFg;
		break;
	}
	

	switch (DataBank::Instance()->GetPlayerType())
	{
	case (int)Player::PlayerTypeTrumpet:
		for (int i = 0; i < MAX_CHARA_OBJ; i++)
		{
			if (chara_objects[i] == nullptr)
			{
				chara_objects[i] = new TrpPlayer;
				break;
			}
		}
		break;
	case (int)Player::PlayerTypeFlute:
		for (int i = 0; i < MAX_CHARA_OBJ; i++)
		{
			if (chara_objects[i] == nullptr)
			{
				chara_objects[i] = new FlutePlayer;
				break;
			}
		}
		break;
	case (int)Player::PlayerTypeTuba:
		for (int i = 0; i < MAX_CHARA_OBJ; i++)
		{
			if (chara_objects[i] == nullptr)
			{
				chara_objects[i] = new TubaPlayer;
				break;
			}
		}
		break;
	default:
		break;
	}
		
}

void ObjectManager::Update()
{
	for (int i = 0; i < MAX_CHARA_OBJ; i++)
	{
		if (chara_objects[i] != nullptr)
		{
			chara_objects[i]->Update();
		}
	}

	//IsHitTest(GetCharaObject(ObjectRavel::Ravel_Player), GetCharaObject(ObjectRavel::Ravel_Boss));

	//当たり判定
	CollisionManager::GetInstance().Update();

}

void ObjectManager::Draw()
{
	for (int i = 0; i < MAX_CHARA_OBJ; i++)
	{
		if (chara_objects[i] != nullptr)
		{
			chara_objects[i]->Draw();
		}
	}
}

