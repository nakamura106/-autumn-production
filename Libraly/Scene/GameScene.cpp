#include <stdio.h>
#include "../Engine/Input.h"
#include "../Engine/Graphics.h"
#include "../Texture/Texture.h"
#include "../Scene/GameScene.h"
#include "../Map/Map.h"
#include"../Player/TrpPlayer.h"


Map map;
TrpPlayer player;

// �Q�[���{�҃V�[���̏�����
void InitGameScene();
// �Q�[���{�҃V�[���̃��C������
void MainGameScene();
// �Q�[���{�҃V�[���̏I��
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







}



void InitGameScene()
{



	player.Init();

	map.Init();
	



	ChangeSceneStep(SceneStep::MainStep);
}






void MainGameScene()
{






}

SceneId FinishGameScene()
{
	ReleaseCategoryTexture(TEXTURE_CATEGORY_GAME);


	return SceneId::GameEndScene;
}

