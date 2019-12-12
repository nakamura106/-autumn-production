#include <stdio.h>
#include "../Engine/Input.h"
#include "../Engine/Graphics.h"
#include "../Texture/Texture.h"
#include "../Scene/GameScene.h"
#include "../Map/Map.h"
#include"../Player/TrpPlayer.h"
#include"../Enemy/Mouse.h"
#include "../UI/UiManager.h"
#include "../Manager/ObjectManager.h"
#include"../Bullet/PlayerBullet.h"
#include"../Engine/FlameTimer.h"


// �Q�[���{�҃V�[���̏�����
void InitGameScene();
// �Q�[���{�҃V�[���̃��C������
void MainGameScene();
// �Q�[���{�҃V�[���̏I��
SceneId FinishGameScene();

SceneId UpdateGameScene()
{
	switch (GetCurrentSceneStep())
	{
	case SceneStep::InitStep:
		InitGameScene();
		break;
	case SceneStep::MainStep:
		MainGameScene();
		break;
	case SceneStep::EndStep:
		return FinishGameScene();
		break;
	}

	return SceneId::GameScene;
}



void DrawGameScene()
{
	ObjectManager::Instance()->Draw();

	UiManager::Instance()->Draw();

}



void InitGameScene()
{
	ObjectManager::Instance()->CreateObject();

	ObjectManager::Instance()->Init();

	UiManager::Instance()->Create();



	ChangeSceneStep(SceneStep::MainStep);
}



void MainGameScene()
{
	// UpdateInput();
	
	ObjectManager::Instance()->Update();

	UiManager::Instance()->Update();

}

SceneId FinishGameScene()
{
	ReleaseCategoryTexture(TEXTURE_CATEGORY_GAME);


	return SceneId::GameEndScene;
}

