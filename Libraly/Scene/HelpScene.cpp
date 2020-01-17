#include "HelpScene.h"
#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "../Engine/Anime.h"
#include <stdio.h>
#include "Scene.h"
#include "SceneObject/HelpSceneObject.h"
#include"../SceneLoader/HelpSceneLoad/HelpSceneLoad.h"


HelpSceneObject help_object;

// タイトルシーンの初期化

void InitHelpScene();
// タイトルシーンのメイン処理
void MainHelpScene();
// タイトルシーンの終了
SceneId FinishHelpScene();


SceneId UpdateHelpScene()
{
	switch (GetCurrentSceneStep())
	{
	case SceneStep::InitStep:
		InitHelpScene();
		break;
	case SceneStep::MainStep:
		MainHelpScene();
		break;
	case SceneStep::EndStep:
		return FinishHelpScene();
		break;
	}

	return SceneId::HelpScene;
}

void DrawHelpScene()
{
	help_object.Draw();
}

void InitHelpScene()
{
	
	help_object.Init();
	HelpSceneLoad();
	ChangeSceneStep(SceneStep::MainStep);
}

void MainHelpScene()
{
	help_object.Update();

}

SceneId FinishHelpScene()
{
	ReleaseCategoryTexture(TEXTURE_CATEGORY_HELP);
	return SceneId::TitleScene;

}
