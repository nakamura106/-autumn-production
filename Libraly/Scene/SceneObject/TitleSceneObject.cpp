#include "TitleSceneObject.h"
#include "../../Texture/Texture.h"
#include "../../Engine/Graphics.h"
#include "../../Engine/Input.h"
#include "../Scene.h"
#include <string>

TitleSceneObject::TitleSceneObject()
{
	m_mouse_pos.x = 0.0f;
	m_mouse_pos.y = 0.0f;
	m_help_flag = false;
	m_select_flag = false;
}

TitleSceneObject::~TitleSceneObject()
{
}

void TitleSceneObject::Init()
{
	LoadTexture("Res/Tex/TitleScene/Title.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleBgTex);
	LoadTexture("Res/Tex/TitleScene/Continue1.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleContinue1Tex);
	LoadTexture("Res/Tex/TitleScene/Continue2.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleContinue2Tex);
	LoadTexture("Res/Tex/TitleScene/Help1.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleHelp1Tex);
	LoadTexture("Res/Tex/TitleScene/Help2.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleHelp2Tex);
	LoadTexture("Res/Tex/TitleScene/Logo.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleLogoTex);
	LoadTexture("Res/Tex/TitleScene/GameStart1.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleStart1Tex);
	LoadTexture("Res/Tex/TitleScene/GameStart2.png", TEXTURE_CATEGORY_TITLE, TitleCategoryTextureList::TitleStart2Tex);
	

	for (int i = 0; i < 5; i++)
	{
		m_draw_pos[i].x = 0.0f;
		m_draw_pos[i].y = 0.0f;
		m_param[i].category_id = TEXTURE_CATEGORY_TITLE;
	}
	m_param[0].texture_id = TitleCategoryTextureList::TitleBgTex;
	m_draw_pos[0].x = 0.0f;
	m_draw_pos[0].y = 0.0f;
	m_param[1].texture_id = TitleCategoryTextureList::TitleLogoTex;
	m_draw_pos[1].x = 700.0f;
	m_draw_pos[1].y = 100.0f;
	m_param[2].texture_id = TitleCategoryTextureList::TitleStart2Tex;
	m_draw_pos[2].x = 1380.0f;
	m_draw_pos[2].y = 460.0f;
	m_param[3].texture_id = TitleCategoryTextureList::TitleContinue2Tex;
	m_draw_pos[3].x = 1380.0f;
	m_draw_pos[3].y = 540.0f;
	m_param[4].texture_id = TitleCategoryTextureList::TitleHelp2Tex;
	m_draw_pos[4].x = 1380.0f;
	m_draw_pos[4].y = 620.0f;

	
}

void TitleSceneObject::Update()
{
	UpdateInput();

	m_mouse_pos.x = GetMousePos().X;
	m_mouse_pos.y = GetMousePos().Y;

	if (m_draw_pos[2].x < m_mouse_pos.x && m_mouse_pos.x < m_draw_pos[2].x + 289.0f
		&& m_draw_pos[2].y < m_mouse_pos.y && m_mouse_pos.y < m_draw_pos[2].y + 60.0f) {
		m_param[2].texture_id = TitleCategoryTextureList::TitleStart1Tex;
		if (OnMousePush(Left) == true){
			m_select_flag = true;
			ChangeSceneStep(SceneStep::EndStep);
		}
	}
	else {
		m_param[2].texture_id = TitleCategoryTextureList::TitleStart2Tex;
	}

	if (m_draw_pos[3].x <= m_mouse_pos.x && m_mouse_pos.x <= m_draw_pos[3].x + 221.0f
		&& m_draw_pos[3].y <= m_mouse_pos.y && m_mouse_pos.y <= m_draw_pos[3].y + 51.0f) {
		m_param[3].texture_id = TitleCategoryTextureList::TitleContinue1Tex;
		if (OnMousePush(Left) == true){
			m_select_flag = true;
			ChangeSceneStep(SceneStep::EndStep);
		}
	}
	else {
		m_param[3].texture_id = TitleCategoryTextureList::TitleContinue2Tex;
	}

	if (m_draw_pos[4].x <= m_mouse_pos.x && m_mouse_pos.x <= m_draw_pos[4].x + 142.0f
		&& m_draw_pos[4].y <= m_mouse_pos.y && m_mouse_pos.y <= m_draw_pos[4].y + 50.0f) {
		m_param[4].texture_id = TitleCategoryTextureList::TitleHelp1Tex;
		if (OnMousePush(Left) == true){
			m_help_flag = true;
			ChangeSceneStep(SceneStep::EndStep);
		}
	}
	else {
		m_param[4].texture_id = TitleCategoryTextureList::TitleHelp2Tex;
	}

}

void TitleSceneObject::Draw()
{
	DrawTexture(m_draw_pos[0].x, m_draw_pos[0].y, GetTexture(m_param[0].category_id, m_param[0].texture_id));
	DrawTexture(m_draw_pos[1].x, m_draw_pos[1].y, GetTexture(m_param[1].category_id, m_param[1].texture_id));
	DrawTexture(m_draw_pos[2].x, m_draw_pos[2].y, GetTexture(m_param[2].category_id, m_param[2].texture_id));
	DrawTexture(m_draw_pos[3].x, m_draw_pos[3].y, GetTexture(m_param[3].category_id, m_param[3].texture_id));
	DrawTexture(m_draw_pos[4].x, m_draw_pos[4].y, GetTexture(m_param[4].category_id, m_param[4].texture_id));
}
