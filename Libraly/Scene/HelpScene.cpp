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
	DrawTexture(0.0f, 0.0f, GetTexture(TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::HelpBgTex));
	DrawTexture(0.0f, 0.0f, GetTexture(TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::Help1Tex));

}

void InitHelpScene()
{
	LoadTexture("Res/Tex/TitleScene/Title.png", TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::HelpBgTex);
	LoadTexture("Res/Tex/HelpScene/Help1.png", TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::Help1Tex);
	LoadTexture("Res/Tex/HelpScene/Help2.png", TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::Help2Tex);
	LoadTexture("Res/Tex/HelpScene/Help3.png", TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::Help3Tex);

	ChangeSceneStep(SceneStep::MainStep);
}

void MainHelpScene()
{


}

SceneId FinishHelpScene()
{

	return SceneId::GameScene;

}
