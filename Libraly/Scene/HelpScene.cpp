#include "HelpScene.h"
#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "../Engine/Anime.h"
#include <stdio.h>
#include "Scene.h"


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


}

void InitHelpScene()
{




	ChangeSceneStep(SceneStep::MainStep);
}



void MainHelpScene()
{


}

SceneId FinishHelpScene()
{

	return SceneId::GameScene;

}
