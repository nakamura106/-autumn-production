#include "HelpSceneObject.h"
#include "../../Texture/Texture.h"
#include "../../Engine/Graphics.h"
#include "../../Engine/Input.h"
#include "../Scene.h"

HelpSceneObject::HelpSceneObject()
{
	for (int i = 0; i < 2; i++)
	{
		m_draw_pos[i].x = 0.0f;
		m_draw_pos[i].y = 0.0f;

		m_param[i].category_id = TEXTURE_CATEGORY_HELP;
	}
}

HelpSceneObject::~HelpSceneObject()
{
}

void HelpSceneObject::Init()
{
	LoadTexture("Res/Tex/TitleScene/Title.png", TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::HelpBgTex);
	LoadTexture("Res/Tex/HelpScene/Help1.png", TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::Help1Tex);
	LoadTexture("Res/Tex/HelpScene/Help2.png", TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::Help2Tex);
	LoadTexture("Res/Tex/HelpScene/Help3.png", TEXTURE_CATEGORY_HELP, HelpCategoryTextureList::Help3Tex);

	m_param[0].texture_id = HelpCategoryTextureList::HelpBgTex;
	m_param[1].texture_id = HelpCategoryTextureList::Help1Tex;
}

void HelpSceneObject::Update()
{
	if (OnMouseDown(Left) == true)
	{
		if (m_param[1].texture_id == HelpCategoryTextureList::Help1Tex)
		{
			m_param[1].texture_id = HelpCategoryTextureList::Help2Tex;
		}
		else if (m_param[1].texture_id == HelpCategoryTextureList::Help2Tex)
		{
			m_param[1].texture_id = HelpCategoryTextureList::Help3Tex;
		}
		else if (m_param[1].texture_id == HelpCategoryTextureList::Help3Tex)
		{
			ChangeSceneStep(SceneStep::EndStep);
		}
	}
}

void HelpSceneObject::Draw()
{
	DrawTexture(m_draw_pos[0].x, m_draw_pos[0].y, GetTexture(m_param[0].category_id, m_param[0].texture_id));
	DrawTexture(m_draw_pos[1].x, m_draw_pos[1].y, GetTexture(m_param[1].category_id, m_param[1].texture_id));
}
