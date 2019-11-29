#include <stdio.h>
#include "../Engine/Input.h"
#include "../Engine/Graphics.h"
#include "../Texture/Texture.h"
#include "../Scene/GameScene.h"
#include "../Map/Map.h"
#include"../Player/TrpPlayer.h"
#include"../Enemy/EnemyBase.h"
#include "../UI/UiManager.h"


Map map;
TrpPlayer player;
EnemyBase enemy;


// ゲーム本編シーンの初期化
void InitGameScene();
// ゲーム本編シーンのメイン処理
void MainGameScene();
// ゲーム本編シーンの終了
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



	map.Draw();

	player.Draw();

	//enemy.Draw();

	UiManager::Instance()->Draw();

}



void InitGameScene()
{
	player.Init();

	map.Init();
	
	enemy.Init();

	UiManager::Instance()->Create();


	ChangeSceneStep(SceneStep::MainStep);
}



void MainGameScene()
{
	UpdateInput();

	player.Update();

	//enemy.Update();

	map.Update();

}

SceneId FinishGameScene()
{
	ReleaseCategoryTexture(TEXTURE_CATEGORY_GAME);


	return SceneId::GameEndScene;
}

