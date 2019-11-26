#include "UiManager.h"

UiManager* UiManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new UiManager;
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
}

void UiManager::Update()
{
	for (int i = 0; i < MAX_UI_OBJ; i++)
	{
		
	}
}

void UiManager::Draw()
{
	for (int i = 0; i < MAX_UI_OBJ; i++)
	{

	}
}