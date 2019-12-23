#include "SelectScene.h"
#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "../Engine/Anime.h"
#include <stdio.h>
#include "Scene.h"
#include "SceneObject/SelectSceneObject.h"

SelectSceneObject select_object;


// タイトルシーンの初期化

void InitSelectScene();
// タイトルシーンのメイン処理
void MainSelectScene();
// タイトルシーンの終了
SceneId FinishSelectScene();


SceneId UpdateSelectScene()
{
	switch (GetCurrentSceneStep())
	{
	case SceneStep::InitStep:
		InitSelectScene();
		break;
	case SceneStep::MainStep:
		MainSelectScene();
		break;
	case SceneStep::EndStep:
		return FinishSelectScene();
		break;
	}

	return SceneId::SelectScene;
}

void DrawSelectScene()
{
	select_object.Draw();

}

void InitSelectScene()
{
	select_object.Init();



	ChangeSceneStep(SceneStep::MainStep);
}



void MainSelectScene()
{
	select_object.Update();

}

SceneId FinishSelectScene()
{
	ReleaseCategoryTexture(TEXTURE_CATEGORY_SELECT);
	return SceneId::GameScene;

}
