#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "../Scene/GameEndScene.h"
#include "../Engine/Sound.h"
#include "../Scene/Scene.h"
#include "SceneObject/EndSceneObject.h"
#include"../SceneLoader/GameEndSceneLoad/GameEndSceneLoad.h"

EndSceneObject end_object;

// ヘルプシーンの初期化
void InitGameEndScene();
// ヘルプシーンのメイン
void MainGameEndScene();
// ヘルプシーンの終了
SceneId FinishGameEndScene();

SceneId UpdateGameEndScene()
{
	switch (GetCurrentSceneStep())
	{
	case SceneStep::InitStep:
		InitGameEndScene();
		break;
	case SceneStep::MainStep:
		MainGameEndScene();
		break;
	case SceneStep::EndStep:
		return FinishGameEndScene();
		break;
	}

	return SceneId::GameEndScene;
}


void DrawGameEndScene()
{
	end_object.Draw();

}

void InitGameEndScene()
{
	end_object.Init();
	GameEndSceneLoad();
	ChangeSceneStep(SceneStep::MainStep);
}

void MainGameEndScene()
{

	end_object.Update();

	if (OnMouseDown(Left) == true) {
		ChangeSceneStep(SceneStep::EndStep);
	}
}

SceneId FinishGameEndScene()
{
	ReleaseCategoryTexture(TEXTURE_CATEGORY_GAMEEND);

	return SceneId::TitleScene;
}
