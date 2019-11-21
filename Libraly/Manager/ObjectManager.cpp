#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	Init();
}

ObjectManager::~ObjectManager()
{
	for (int i = 0; i < 50; i++)
	{
		if (chara_objects[i] != nullptr)
		{
			delete chara_objects[i];
			chara_objects[i] = nullptr;
		}
		if (bullets_objects[i] != nullptr)
		{
			delete bullets_objects[i];
			bullets_objects[i] = nullptr;
		}
	}
}

// ポインタ配列の中身にすべてNULLを入れておく
void ObjectManager::Init()
{
	for (int i = 0; i < 100; i++)
	{
		if (i < 50 && chara_objects[i] != nullptr)
		{
			chara_objects[i] = nullptr;
		}

		if (bullets_objects[i] != nullptr)
		{
			bullets_objects[i] = nullptr;

		}
	}
}

void ObjectManager::CreateObject()
{
	for (int i = 0; i < 100; i++)
	{
		if (i < 50)
		{
			chara_objects[i]->Create();
		}

		bullets_objects[i]->Create();
	}
}

void ObjectManager::Update()
{
	for (int i = 0; i < 100; i++)
	{
		if (i < 50)
		{
			chara_objects[i]->Update();
		}

		bullets_objects[i]->Update();
	}
}

void ObjectManager::Draw()
{
	for (int i = 0; i < 100; i++)
	{
		if (i < 50)
		{
			chara_objects[i]->Draw();
		}

		bullets_objects[i]->Draw();
	}
}
