#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "../Scene/TitleScene.h"
#include "../Engine/Anime.h"
#include <stdio.h>
#include "../Scene/Scene.h"


// タイトルシーンの初期化

void InitTitleScene();
// タイトルシーンのメイン処理
void MainTitleScene();
// タイトルシーンの終了
SceneId FinishTitleScene();

Vec2 test;


void StartDraw() {
	
}

void EndDraw()
{
	
}

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

	StartDraw();
	EndDraw();

}

void InitTitleScene()
{




	ChangeSceneStep(SceneStep::MainStep);
}



void MainTitleScene()
{
	

}

SceneId FinishTitleScene()
{
	
		return SceneId::GameScene;
	
}
