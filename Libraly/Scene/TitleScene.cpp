#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "../Scene/TitleScene.h"
#include "../Engine/Anime.h"
#include <stdio.h>
#include <string>
#include "../Scene/Scene.h"
#include "SceneObject/TitleSceneObject.h"
#include"../SceneLoader/TitleSceneLoad/TitleSceneLoad.h"
#include "../Sound/SoundManager.h"

TitleSceneObject title_obj;

// タイトルシーンの初期化

void InitTitleScene();
// タイトルシーンのメイン処理
void MainTitleScene();
// タイトルシーンの終了
SceneId FinishTitleScene();


SceneId UpdateTitleScene()
{
	switch (GetCurrentSceneStep())
	{
	case SceneStep::InitStep:
		InitTitleScene();
		break;
	case SceneStep::MainStep:
		MainTitleScene();
		break;
	case SceneStep::EndStep:
		return FinishTitleScene();
		break;
	}

	return SceneId::TitleScene;
}

void DrawTitleScene()
{

	title_obj.Draw();
}

void InitTitleScene()
{
	title_obj.Init();
	TitleSceneLoad();

	ChangeSceneStep(SceneStep::MainStep);
}


void MainTitleScene()
{
	title_obj.Update();
	
}

SceneId FinishTitleScene()
{
	ReleaseCategoryTexture(TEXTURE_CATEGORY_TITLE);
	SoundManager::Instance()->ReleaseTitleSound();

	return SceneId::SelectScene;
}
