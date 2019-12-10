#include "ObjectManager.h"
#include "../Player/TrpPlayer.h"
#include "../Map/Map.h"
#include "../Enemy/Mouse.h"


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
	chara_objects[0] = new Map();

	chara_objects[1] = new HedgeHog();

	chara_objects[2] = new TrpPlayer();
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

	IsHitTest(GetCharaObject(ObjectRavel::Ravel_Player), GetCharaObject(ObjectRavel::Ravel_Boss));

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

