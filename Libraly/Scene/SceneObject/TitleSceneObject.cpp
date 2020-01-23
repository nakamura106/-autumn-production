#include "TitleSceneObject.h"
#include "../../Texture/Texture.h"
#include "../../Engine/Graphics.h"
#include "../../Engine/Input.h"
#include "../Scene.h"
#include "../../Sound/SoundManager.h"
#include <string>

TitleSceneObject::TitleSceneObject()
{
	m_mouse_pos.x = 0.0f;
	m_mouse_pos.y = 0.0f;

	m_scene_state = TitleSceneState::Home;
}

TitleSceneObject::~TitleSceneObject()
{
}

void TitleSceneObject::Init()
{


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
	m_param[5].texture_id = TitleCategoryTextureList::Help1Tex;
	m_draw_pos[5].x = 0.f;
	m_draw_pos[5].y = 0.f;

	SoundManager::Instance()->RegisterTitleSound();
	SoundManager::Instance()->SoundBGM();
}

void TitleSceneObject::Update()
{
	m_mouse_pos.x = GetMousePos().X;
	m_mouse_pos.y = GetMousePos().Y;

	switch (m_scene_state)
	{
	case TitleSceneState::Home:
		UpdateHomeScene();
		break;
	case TitleSceneState::Start:
		UpdateStartScene();
		break;
	case TitleSceneState::Continue:
		UpdateContinueScene();
		break;
	case TitleSceneState::Help:
		UpdateHelpScene();
		break;
	}

}

void TitleSceneObject::Draw()
{
	if (m_scene_state == TitleSceneState::Help)
	{
		DrawTexture(m_draw_pos[0].x, m_draw_pos[0].y, GetTexture(m_param[0].category_id, m_param[0].texture_id));
		DrawTexture(m_draw_pos[1].x, m_draw_pos[1].y, GetTexture(m_param[1].category_id, m_param[1].texture_id));
		DrawTexture(m_draw_pos[5].x, m_draw_pos[5].y, GetTexture(m_param[5].category_id, m_param[5].texture_id));
		
	}
	else
	{
		DrawTexture(m_draw_pos[0].x, m_draw_pos[0].y, GetTexture(m_param[0].category_id, m_param[0].texture_id));
		DrawTexture(m_draw_pos[1].x, m_draw_pos[1].y, GetTexture(m_param[1].category_id, m_param[1].texture_id));
		DrawTexture(m_draw_pos[2].x, m_draw_pos[2].y, GetTexture(m_param[2].category_id, m_param[2].texture_id));
		DrawTexture(m_draw_pos[3].x, m_draw_pos[3].y, GetTexture(m_param[3].category_id, m_param[3].texture_id));
		DrawTexture(m_draw_pos[4].x, m_draw_pos[4].y, GetTexture(m_param[4].category_id, m_param[4].texture_id));
	}
}

void TitleSceneObject::UpdateHomeScene()
{
	UpdateSelectSE();

	if (m_draw_pos[2].x < m_mouse_pos.x && m_mouse_pos.x < m_draw_pos[2].x + 289.0f
		&& m_draw_pos[2].y < m_mouse_pos.y && m_mouse_pos.y < m_draw_pos[2].y + 60.0f) {
		m_param[2].texture_id = TitleCategoryTextureList::TitleStart1Tex;
		if (OnMouseDown(Left) == true) {
			SoundManager::Instance()->SoundClickSE();
			m_scene_state = TitleSceneState::Start;
		}
	}
	else {
		m_param[2].texture_id = TitleCategoryTextureList::TitleStart2Tex;
	}

	if (m_draw_pos[3].x <= m_mouse_pos.x && m_mouse_pos.x <= m_draw_pos[3].x + 221.0f
		&& m_draw_pos[3].y <= m_mouse_pos.y && m_mouse_pos.y <= m_draw_pos[3].y + 51.0f) {
		m_param[3].texture_id = TitleCategoryTextureList::TitleContinue1Tex;
		if (OnMouseDown(Left) == true) {
			SoundManager::Instance()->SoundClickSE();
			m_scene_state = TitleSceneState::Continue;
		}
	}
	else {
		m_param[3].texture_id = TitleCategoryTextureList::TitleContinue2Tex;
	}

	if (m_draw_pos[4].x <= m_mouse_pos.x && m_mouse_pos.x <= m_draw_pos[4].x + 142.0f
		&& m_draw_pos[4].y <= m_mouse_pos.y && m_mouse_pos.y <= m_draw_pos[4].y + 50.0f) {
		m_param[4].texture_id = TitleCategoryTextureList::TitleHelp1Tex;
		if (OnMouseDown(Left) == true) {
			SoundManager::Instance()->SoundClickSE();
			m_scene_state = TitleSceneState::Help;
		}
	}
	else {
		m_param[4].texture_id = TitleCategoryTextureList::TitleHelp2Tex;

	}
}

void TitleSceneObject::UpdateStartScene()
{
	m_scene_state = TitleSceneState::Home;
	ChangeSceneStep(SceneStep::EndStep);
}

void TitleSceneObject::UpdateContinueScene()
{
	m_scene_state = TitleSceneState::Home;
	ChangeSceneStep(SceneStep::EndStep);
}

void TitleSceneObject::UpdateHelpScene()
{
	if (OnMouseDown(Left) == true)
	{
		if (m_param[5].texture_id == TitleCategoryTextureList::Help1Tex)
		{
			m_param[5].texture_id = TitleCategoryTextureList::Help2Tex;
			SoundManager::Instance()->SoundClickSE();
		}
		else if (m_param[5].texture_id == TitleCategoryTextureList::Help2Tex)
		{
			m_param[5].texture_id = TitleCategoryTextureList::Help3Tex;
			SoundManager::Instance()->SoundClickSE();
		}
		else if (m_param[5].texture_id == TitleCategoryTextureList::Help3Tex)
		{
			m_param[5].texture_id = TitleCategoryTextureList::Help1Tex;
			SoundManager::Instance()->SoundClickSE();
			m_scene_state = TitleSceneState::Home;
		}
	}

	if (OnMouseDown(Right) == true)
	{
		if (m_param[5].texture_id == TitleCategoryTextureList::Help1Tex)
		{
			SoundManager::Instance()->SoundClickSE();
			m_scene_state = TitleSceneState::Home;
		}
		else if (m_param[5].texture_id == TitleCategoryTextureList::Help2Tex)
		{
			m_param[5].texture_id = TitleCategoryTextureList::Help1Tex;
			SoundManager::Instance()->SoundClickSE();
		}
		else if (m_param[5].texture_id == TitleCategoryTextureList::Help3Tex)
		{
			m_param[5].texture_id = TitleCategoryTextureList::Help2Tex;
			SoundManager::Instance()->SoundClickSE();
		}
	}
}

void TitleSceneObject::UpdateSelectSE()
{
	if (m_draw_pos[2].x < m_mouse_pos.x && m_mouse_pos.x < m_draw_pos[2].x + 289.0f
		&& m_draw_pos[2].y < m_mouse_pos.y && m_mouse_pos.y < m_draw_pos[2].y + 60.0f)	{
		SoundManager::Instance()->SoundSelectSE();
	}
	else if (m_draw_pos[3].x <= m_mouse_pos.x && m_mouse_pos.x <= m_draw_pos[3].x + 221.0f
		&& m_draw_pos[3].y <= m_mouse_pos.y && m_mouse_pos.y <= m_draw_pos[3].y + 51.0f) {
		SoundManager::Instance()->SoundSelectSE();
	}
	else if (m_draw_pos[4].x <= m_mouse_pos.x && m_mouse_pos.x <= m_draw_pos[4].x + 142.0f
		&& m_draw_pos[4].y <= m_mouse_pos.y && m_mouse_pos.y <= m_draw_pos[4].y + 50.0f) {
		SoundManager::Instance()->SoundSelectSE();
	}
	else {
		SoundManager::Instance()->ResetSelectFlag();
	}
}
