#include <stdio.h>
#include "../Engine/Input.h"
#include "../Engine/Graphics.h"
#include "../Texture/Texture.h"
#include "../Scene/GameScene.h"
#include "../Map/Map.h"
#include"../Player/TrpPlayer.h"
#include"../Enemy/Mouse.h"
#include "../UI/UiManager.h"
#include"../Bullet/PlayerBullet.h"
#include"../Engine/FlameTimer.h"


Map map;
TrpPlayer player;
HedgeHog enemy;
PlayerBullet p_bullet(100.f, 700.f, 5.f, Direction::RIGHT);

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

	enemy.Draw();

	player.Draw();

	p_bullet.Draw();

	UiManager::Instance()->Draw();

	FlameTimer::Debug::DrawTimer();

}



void InitGameScene()
{

	map.Init();
	
	enemy.Init();

	player.Init();

	p_bullet.Init();

	UiManager::Instance()->Create();


	ChangeSceneStep(SceneStep::MainStep);
}



void MainGameScene()
{
	UpdateInput();
	
	map.Update();
	
	enemy.Update();

	player.Update();

	p_bullet.Update();

}

SceneId FinishGameScene()
{
	ReleaseCategoryTexture(TEXTURE_CATEGORY_GAME);


	return SceneId::GameEndScene;
}

