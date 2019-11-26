#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	Init();
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
			chara_objects[i] = nullptr;
		}
	}
}

void ObjectManager::CreateObject()
{
	for (int i = 0; i < MAX_CHARA_OBJ; i++)
	{
		
	}
}

void ObjectManager::Update()
{
	for (int i = 0; i < MAX_CHARA_OBJ; i++)
	{
		chara_objects[i]->Update();
	}
}

void ObjectManager::Draw()
{
	for (int i = 0; i < MAX_CHARA_OBJ; i++)
	{
		chara_objects[i]->Draw();
	}
}
