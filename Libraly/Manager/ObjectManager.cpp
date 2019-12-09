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

ObjectBase* ObjectManager::GetCharaObject(int ravel)
{
	if (ravel == (int)ObjectRavel::Ravel_Player)
	{
		return chara_objects[1];
	}
	else if (ravel == (int)ObjectRavel::Ravel_Boss)
	{
		return chara_objects[2];
	}

	return false;
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

// �|�C���^�z��̒��g�ɂ��ׂ�NULL�����Ă���
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
	chara_objects[1] = new TrpPlayer();
	chara_objects[2] = new HedgeHog();

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

	IsHitTest(GetCharaObject((int)ObjectRavel::Ravel_Player), GetCharaObject((int)ObjectRavel::Ravel_Boss));

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

