#include "SelectSceneObject.h"
#include "../../Engine/Graphics.h"
#include "../../Texture/Texture.h"

SelectSceneObject::SelectSceneObject()
{
}

SelectSceneObject::~SelectSceneObject()
{
}

void SelectSceneObject::Init()
{
	LoadTexture("Res/Tex/SelectScene/SelectBg.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::SelectBgTex);
	LoadTexture("Res/Tex/SelectScene/BossSelect.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossSelectBottonTex);
	LoadTexture("Res/Tex/SelectScene/BrassSelect.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BrassSelectBottonTex);
	LoadTexture("Res/Tex/SelectScene/Boss1Image.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossMouseImageTex);
	LoadTexture("Res/Tex/SelectScene/Clear.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::ClearSymbolTex);
	LoadTexture("Res/Tex/SelectScene/Complete.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::CompleteSymbolTex);
	LoadTexture("Res/Tex/SelectScene/Spotlight.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::SpotlightTex);
	LoadTexture("Res/Tex/SelectScene/NumberCollcted.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::NumberCollectedTex);
	LoadTexture("Res/Tex/SelectScene/MouseFrame1.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossMouseFrame1);
	LoadTexture("Res/Tex/SelectScene/MouseFrame2.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossMouseFrame2);
	LoadTexture("Res/Tex/SelectScene/BirdFrame1.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossBirdFrame1);
	LoadTexture("Res/Tex/SelectScene/BirdFrame2.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossBirdFrame2);
	LoadTexture("Res/Tex/SelectScene/BirdFrame3.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossBirdFrame3);
	LoadTexture("Res/Tex/SelectScene/GorillaFrame1.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossGorillaFrame1);
	LoadTexture("Res/Tex/SelectScene/GorillaFrame2.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossGorillaFrame2);
	LoadTexture("Res/Tex/SelectScene/GorillaFrame3.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossGorillaFrame3);
	LoadTexture("Res/Tex/SelectScene/TrpFrame1.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::TrpFrame1);
	LoadTexture("Res/Tex/SelectScene/TrpFrame2.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::TrpFrame2);
	LoadTexture("Res/Tex/SelectScene/FluteFrame1.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::FluteFrame1);
	LoadTexture("Res/Tex/SelectScene/FluteFrame2.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::FluteFrame2);
	LoadTexture("Res/Tex/SelectScene/FluteFrame3.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::FluteFrame3);
	LoadTexture("Res/Tex/SelectScene/TubaFrame1.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::TubaFrame1);
	LoadTexture("Res/Tex/SelectScene/TubaFrame2.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::TubaFrame2);
	LoadTexture("Res/Tex/SelectScene/TubaFrame3.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::TubaFrame3);

}

void SelectSceneObject::Update()
{
}

void SelectSceneObject::Draw()
{

}
