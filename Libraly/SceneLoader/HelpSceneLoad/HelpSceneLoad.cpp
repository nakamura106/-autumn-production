#include"HelpSceneLoad.h"
#include"../../Texture/Texture.h"


void HelpSceneLoad()
{
	LoadTexture("Res/Tex/TitleScene/Title.png", TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::HelpBgTex);
	LoadTexture("Res/Tex/HelpScene/Help1.png", TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::Help1Tex);
	LoadTexture("Res/Tex/HelpScene/Help2.png", TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::Help2Tex);
	LoadTexture("Res/Tex/HelpScene/Help3.png", TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::Help3Tex);
}