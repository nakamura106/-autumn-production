#include <stdio.h>
#include "../Engine/Input.h"
#include "../Engine/Graphics.h"
#include "../Texture/Texture.h"
#include "../Scene/GameScene.h"
#include "../Map/Map.h"
#include"../Player/TrpPlayer.h"
#include"../Enemy/EnemyBase.h"

Map map;
TrpPlayer player;
EnemyBase enemy;

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

	enemy.Draw();





}



void InitGameScene()
{

	

	player.Init();

	map.Init();
	
	enemy.Init();


	ChangeSceneStep(SceneStep::MainStep);
}



void MainGameScene()
{
	UpdateInput();

	player.Update();

	enemy.Update();

}

SceneId FinishGameScene()
{
	ReleaseCategoryTexture(TEXTURE_CATEGORY_GAME);


	return SceneId::GameEndScene;
}

