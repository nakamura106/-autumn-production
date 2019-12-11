#include "HelpScene.h"
#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "../Engine/Anime.h"
#include <stdio.h>
#include "Scene.h"


// �^�C�g���V�[���̏�����

void InitHelpScene();
// �^�C�g���V�[���̃��C������
void MainHelpScene();
// �^�C�g���V�[���̏I��
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
