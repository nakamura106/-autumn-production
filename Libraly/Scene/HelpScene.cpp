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
