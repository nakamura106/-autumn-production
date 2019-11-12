#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Texture/Texture.h"
#include "../Scene/GameEndScene.h"
#include "../Engine/Sound.h"
#include "../Scene/Scene.h"

// �w���v�V�[���̏�����
void InitGameEndScene();
// �w���v�V�[���̃��C��
void MainGameEndScene();
// �w���v�V�[���̏I��
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
	

}

void InitGameEndScene()
{
	
	ChangeSceneStep(SceneStep::MainStep);
}

void MainGameEndScene()
{



	if (OnMouseDown(Left) == true) {
		ChangeSceneStep(SceneStep::EndStep);
	}
}

SceneId FinishGameEndScene()
{
	ReleaseCategoryTexture(TEXTURE_CATEGORY_GAMEEND);

	return SceneId::TitleScene;
}
