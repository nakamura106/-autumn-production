#include "SelectScene.h"
#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "../Engine/Anime.h"
#include <stdio.h>
#include "Scene.h"


// �^�C�g���V�[���̏�����

void InitSelectScene();
// �^�C�g���V�[���̃��C������
void MainSelectScene();
// �^�C�g���V�[���̏I��
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


}

void InitSelectScene()
{




	ChangeSceneStep(SceneStep::MainStep);
}



void MainSelectScene()
{


}

SceneId FinishSelectScene()
{

	return SceneId::GameScene;

}
