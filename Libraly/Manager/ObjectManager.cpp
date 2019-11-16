#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	for (int i = 0; i < 50; i++)
	{
		if (chara_objects[i] != nullptr)
		{
			chara_objects[i] = nullptr;
		}
		if (bullets_objects[i] != nullptr)
		{
			bullets_objects[i] = nullptr;
		}
	}
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

void ObjectManager::CreateObject()
{

}

void ObjectManager::Update()
{
}

void ObjectManager::Draw()
{
}
