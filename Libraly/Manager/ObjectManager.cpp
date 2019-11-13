#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	for (int i = 0; i < 50; i++)
	{
		if (objects[i] != nullptr)
		{
			objects[i] = nullptr;
		}
	}
}

ObjectManager::~ObjectManager()
{
	for (int i = 0; i < 50; i++)
	{
		if (objects[i] != nullptr)
		{
			delete objects[i];
			objects[i] = nullptr;
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
