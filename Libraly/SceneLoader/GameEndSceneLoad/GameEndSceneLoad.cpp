#include"../../Texture/Texture.h"
#include"GameEndSceneLoad.h"

void GameEndSceneLoad()
{
	LoadTexture("Res/Tex/EndScene/Back.png", TEXTURE_CATEGORY_GAMEEND, GameEndCategoryTextureList::GameBuckTex);
	LoadTexture("Res/Tex/EndScene/GameClear.png", TEXTURE_CATEGORY_GAMEEND, GameEndCategoryTextureList::GameClearBgTex);
}