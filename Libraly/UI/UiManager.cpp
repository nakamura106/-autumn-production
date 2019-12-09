#include "UiManager.h"


UiManager* UiManager::p_instance = 0;

UiManager* UiManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new UiManager();
	}

	return p_instance;
}

UiManager::UiManager()
{
	Init();
}

UiManager::~UiManager()
{
	for (int i = 0; i < MAX_UI_OBJ; i++)
	{
		if (ui_objects[i] != nullptr)
		{
			delete ui_objects[i];
			ui_objects[i] = nullptr;
		}
	}
}

void UiManager::Init()
{
	for (int i = 0; i < MAX_UI_OBJ; i++)
	{
		if (ui_objects[i] != nullptr)
		{
			ui_objects[i] = nullptr;
		}
	}
}

void UiManager::Create()
{
	ui_objects[0] = new PlayerBaseUi();
	ui_objects[1] = new PlayerHpUi();
	ui_objects[2] = new PlayerBulletUi();
	ui_objects[3] = new FatigueGaugeUi();
	ui_objects[4] = new SleepGaugeUi();
	ui_objects[5] = new EnemyBaseUi();
}

void UiManager::Update()
{
	for (int i = 0; i < MAX_UI_OBJ; i++)
	{
		if (ui_objects[i] != nullptr)
		{
			ui_objects[i]->Update();
		}
	}
}

void UiManager::Draw()
{
	for (int i = 0; i < MAX_UI_OBJ; i++)
	{
		if (ui_objects[i] != nullptr)
		{
			ui_objects[i]->Draw();
		}
	}
}