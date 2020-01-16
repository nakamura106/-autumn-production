#include "../Scene/Scene.h"
#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/GameEndScene.h"
#include "HelpScene.h"
#include "SelectScene.h"


static SceneId g_CurrentSceneId = SceneId::GameScene;		// 動作中シーンID
		

static SceneStep g_CurrentSceneStep = SceneStep::InitStep;	// 動作中シーンのステ

SceneId GetCurrentSceneId()
{
	return g_CurrentSceneId;
}

SceneStep GetCurrentSceneStep()
{
	return g_CurrentSceneStep;
}

void ChangeSceneStep(SceneStep next_step)
{
	g_CurrentSceneStep = next_step;
}

void UpdateScene()
{
	UpdateInput();

	SceneId scene_id = g_CurrentSceneId;
	switch (g_CurrentSceneId)
	{
	case SceneId::TitleScene:
		scene_id = UpdateTitleScene();
		break;
	case SceneId::HelpScene:
		scene_id = UpdateHelpScene();
		break;
	case SceneId::SelectScene:
		scene_id = UpdateSelectScene();
		break;
	case SceneId::GameEndScene:
		scene_id = UpdateGameEndScene();
		break;
	case SceneId::GameScene:
		scene_id = UpdateGameScene();
		break;
	}

	DrawScene();

	if (scene_id != g_CurrentSceneId)
	{
		g_CurrentSceneId = scene_id;
		ChangeSceneStep(SceneStep::InitStep);
	}
}

void DrawScene()
{
	if (DrawStart() == false)
	{
		return;
	}
	if (g_CurrentSceneStep == SceneStep::MainStep)
	{
		switch (g_CurrentSceneId)
		{
		case SceneId::TitleScene:
			DrawTitleScene();
			break;
		case SceneId::HelpScene:
			DrawHelpScene();
			break;
		case SceneId::SelectScene:
			DrawSelectScene();
			break;
		case SceneId::GameScene:
			DrawGameScene();
			break;
		case SceneId::GameEndScene:
			DrawGameEndScene();
			break;
			;
		}
	}

	DrawEnd();
}