#include "ObjectManager.h"
#include "../Player/TrpPlayer.h"


ObjectManager* ObjectManager::p_instance = 0;

ObjectManager* ObjectManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new ObjectManager;
	}

	return  p_instance;
}

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

// �|�C���^�z��̒��g�ɂ��ׂ�NULL�����Ă���
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

//	chara_objects[0] = new TrpPlayer();

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
