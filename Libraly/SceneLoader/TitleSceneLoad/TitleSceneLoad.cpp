#include"TitleSceneLoad.h"
#include"../../Texture/Texture.h"


void TitleSceneLoad()
{
	LoadTexture("Res/Tex/TitleScene/Title.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleBgTex);
	LoadTexture("Res/Tex/TitleScene/Continue1.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleContinue1Tex);
	LoadTexture("Res/Tex/TitleScene/Continue2.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleContinue2Tex);
	LoadTexture("Res/Tex/TitleScene/Help1.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleHelp1Tex);
	LoadTexture("Res/Tex/TitleScene/Help2.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleHelp2Tex);
	LoadTexture("Res/Tex/TitleScene/Logo.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleLogoTex);
	LoadTexture("Res/Tex/TitleScene/GameStart1.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleStart1Tex);
	LoadTexture("Res/Tex/TitleScene/GameStart2.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleStart2Tex);
}