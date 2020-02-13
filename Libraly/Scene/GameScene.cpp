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
#include "../DataBank/DataBank.h"
#include "../Manager/CollisionManager.h"
#include"../SceneLoader/GameSceneLoad/GameSceneLoad.h"
#include "../Sound/SoundManager.h"


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
	
	ObjectManager::Instance()->Draw();

	UiManager::Instance()->Draw();

}



void InitGameScene()
{

	ObjectManager::Instance()->CreateObject();

	ObjectManager::Instance()->Init();

	UiManager::Instance()->Init();

	UiManager::Instance()->Create();

	GameSceneLoad();

	SoundManager::Instance()->RegisterGameMainSound();
	SoundManager::Instance()->SoundBGM();

	DataBank::Instance()->SetGameStartFlame(FlameTimer::GetNowFlame());

	ChangeSceneStep(SceneStep::MainStep);

}



void MainGameScene()
{
	// UpdateInput();
	
	ObjectManager::Instance()->Update();

	CollisionManager::GetInstance().Update();

	UiManager::Instance()->Update();

	if (DataBank::Instance()->GetIsGameClear() == true)
	{
		DataBank::Instance()->SetGameEndFlame(FlameTimer::GetNowFlame(DataBank::Instance()->GetGameStartFlame()));
		ChangeSceneStep(SceneStep::EndStep);
	}

}

SceneId FinishGameScene()
{

	SoundManager::Instance()->ReleaseBattleSound();
	ReleaseCategoryTexture(TEXTURE_CATEGORY_GAME);
	ObjectManager::Instance()->AllDaleteObject();
	DataBank::Instance()->ResetData();
	UiManager::Instance()->AllDaleteUI();


	return SceneId::GameEndScene;
}

