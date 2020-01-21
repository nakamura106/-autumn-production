#include "SelectSceneObject.h"
#include "../../Engine/Graphics.h"
#include "../../Texture/Texture.h"
#include "../../Engine/Input.h"
#include "../Scene.h"
#include"../../DataBank/DataBank.h"
#include"../../Object/Definition.h"

SelectSceneObject::SelectSceneObject()
{
	for (int i = 0; i < 9; i++)
	{
		m_pos[i].x = 0.0f;
		m_pos[i].y = 0.0f;
		m_param[i].category_id = TEXTURE_CATEGORY_SELECT;
	}
	is_hit_mouse = false;
	is_brass_scene = false;
}

SelectSceneObject::~SelectSceneObject()
{
}

void SelectSceneObject::Init()
{
	

	// 描画する、しないのパラメータがあると分けやすいかも
	m_param[0].texture_id = SelectCategoryTextureList::SelectBgTex;
	m_pos[0].x = 0.0f;
	m_pos[0].y = 0.0f;
	m_param[1].texture_id = SelectCategoryTextureList::BossSelectBottonTex;
	m_pos[1].x = 1050.0f;
	m_pos[1].y = 800.0f;
	m_param[2].texture_id = SelectCategoryTextureList::BossMouseImageTex;
	m_pos[2].x = 0.0f;
	m_pos[2].y = 0.0f;
	m_param[3].texture_id = SelectCategoryTextureList::ClearSymbolTex;
	m_pos[3].x = 330.0f;
	m_pos[3].y = 300.0f;
	m_param[4].texture_id = SelectCategoryTextureList::NumberCollectedTex;
	m_pos[4].x = 100.0f;
	m_pos[4].y = 500.0f;
	m_param[5].texture_id = SelectCategoryTextureList::BossMouseFrame2;	// 349:349
	m_pos[5].x = 850.0f;
	m_pos[5].y = 350.0f;
	m_param[6].texture_id = SelectCategoryTextureList::BossBirdFrame2;
	m_pos[6].x = 1200.0f;
	m_pos[6].y = 350.0f;
	m_param[7].texture_id = SelectCategoryTextureList::BossGorillaFrame3;
	m_pos[7].x = 1550.0f;
	m_pos[7].y = 350.0f;
	m_param[8].texture_id = SelectCategoryTextureList::SpotlightTex;
	m_pos[8].x = 850.0f;
	m_pos[8].y = 200.0f;
	


}

void SelectSceneObject::Update()
{
	m_mouse_pos.x = GetMousePos().X;
	m_mouse_pos.y = GetMousePos().Y;

	if (OnMouseDown(Right) == true)
	{
		is_brass_scene = false;
	}


	if (is_brass_scene == false) {
		BossSelectUpdate();
	}
	else {
		BrassSelectUpdate();
	}
	

}

void SelectSceneObject::Draw()
{
	for (int i = 0; i < 8; i++)
	{
		DrawTexture(m_pos[i].x, m_pos[i].y, GetTexture(m_param[i].category_id, m_param[i].texture_id));
	}
	if (is_hit_mouse == true)
	{
		DrawTexture(m_pos[8].x, m_pos[8].y, GetTexture(m_param[8].category_id, m_param[8].texture_id));
	}
}

void SelectSceneObject::BossSelectUpdate()
{
	m_param[1].texture_id = SelectCategoryTextureList::BossSelectBottonTex;
	m_param[4].texture_id = SelectCategoryTextureList::NumberCollectedTex;
	m_param[7].texture_id = SelectCategoryTextureList::BossGorillaFrame2;

	if (m_pos[5].x < m_mouse_pos.x && m_mouse_pos.x < m_pos[5].x + 349.0f
		&& m_pos[5].y < m_mouse_pos.y && m_mouse_pos.y < m_pos[5].y + 349.0f) {
		m_param[6].texture_id = SelectCategoryTextureList::BossBirdFrame2;
		m_param[5].texture_id = SelectCategoryTextureList::BossMouseFrame1;
		m_param[7].texture_id = SelectCategoryTextureList::BossGorillaFrame2;

		m_pos[8].x = m_pos[5].x;
		is_hit_mouse = true;
		if (OnMouseDown(Left) == true)
		{
			DataBank::Instance()->SetMapType((int)MapType::WoodsMap);
			is_brass_scene = true;
		}
	}
	else if (m_pos[6].x < m_mouse_pos.x && m_mouse_pos.x < m_pos[6].x + 349.0f
		&& m_pos[6].y < m_mouse_pos.y && m_mouse_pos.y < m_pos[6].y + 349.0f) {
		m_param[5].texture_id = SelectCategoryTextureList::BossMouseFrame2;
		m_param[6].texture_id = SelectCategoryTextureList::BossBirdFrame1;
		m_param[7].texture_id = SelectCategoryTextureList::BossGorillaFrame2;
		m_pos[8].x = m_pos[6].x;
		is_hit_mouse = true;
		if (OnMouseDown(Left) == true)
		{
			DataBank::Instance()->SetMapType((int)MapType::SeaMap);
			is_brass_scene = true;
		}
	}
	else if (m_pos[7].x < m_mouse_pos.x && m_mouse_pos.x < m_pos[7].x + 349.0f
		&& m_pos[7].y < m_mouse_pos.y && m_mouse_pos.y < m_pos[7].y + 349.0f)
	{
		m_param[5].texture_id = SelectCategoryTextureList::BossMouseFrame2;
		m_param[6].texture_id = SelectCategoryTextureList::BossBirdFrame2;
		m_param[7].texture_id = SelectCategoryTextureList::BossGorillaFrame1;
		m_pos[8].x = m_pos[7].x;
		is_hit_mouse = true;
		if (OnMouseDown(Left) == true)
		{
			DataBank::Instance()->SetMapType((int)MapType::CityMap);
			is_brass_scene = true;
		}
	}
	else {
		m_param[5].texture_id = SelectCategoryTextureList::BossMouseFrame2;
		m_param[6].texture_id = SelectCategoryTextureList::BossBirdFrame2;
		m_param[7].texture_id = SelectCategoryTextureList::BossGorillaFrame2;
		is_hit_mouse = false;
	}
}

void SelectSceneObject::BrassSelectUpdate()
{
	m_param[1].texture_id = SelectCategoryTextureList::BrassSelectBottonTex;
	m_param[4].texture_id = SelectCategoryTextureList::TimeSymbolTex;
	m_param[6].texture_id = SelectCategoryTextureList::FluteFrame3;
	m_param[7].texture_id = SelectCategoryTextureList::TubaFrame3;

	if (m_pos[5].x < m_mouse_pos.x && m_mouse_pos.x < m_pos[5].x + 349.0f
		&& m_pos[5].y < m_mouse_pos.y && m_mouse_pos.y < m_pos[5].y + 349.0f) {
		m_param[5].texture_id = SelectCategoryTextureList::TrpFrame1;
		m_param[6].texture_id = SelectCategoryTextureList::FluteFrame2;
		m_param[7].texture_id = SelectCategoryTextureList::TubaFrame2;
		m_pos[8].x = m_pos[5].x;
		is_hit_mouse = true;
		if (OnMouseDown(Left) == true)
		{
			DataBank::Instance()->SetPlayerType((int)Player::PlayerTypeTrumpet);
			is_brass_scene = false;
			ChangeSceneStep(SceneStep::EndStep);
		}
	}
	else if (m_pos[6].x < m_mouse_pos.x && m_mouse_pos.x < m_pos[6].x + 349.0f
		&& m_pos[6].y < m_mouse_pos.y && m_mouse_pos.y < m_pos[6].y + 349.0f) {
		m_param[5].texture_id = SelectCategoryTextureList::TrpFrame2;
		m_param[6].texture_id = SelectCategoryTextureList::FluteFrame1;
		m_param[7].texture_id = SelectCategoryTextureList::TubaFrame2;
		m_pos[8].x = m_pos[6].x;
		is_hit_mouse = true;
		if (OnMouseDown(Left) == true)
		{
			DataBank::Instance()->SetPlayerType((int)Player::PlayerTypeFlute);
			is_brass_scene = false;
			ChangeSceneStep(SceneStep::EndStep);
		}
	}
	else if (m_pos[7].x < m_mouse_pos.x && m_mouse_pos.x < m_pos[7].x + 349.0f
		&& m_pos[7].y < m_mouse_pos.y && m_mouse_pos.y < m_pos[7].y + 349.0f)
	{
		m_param[5].texture_id = SelectCategoryTextureList::TrpFrame2;
		m_param[6].texture_id = SelectCategoryTextureList::FluteFrame2;
		m_param[7].texture_id = SelectCategoryTextureList::TubaFrame1;
		m_pos[8].x = m_pos[7].x;
		is_hit_mouse = true;
		if (OnMouseDown(Left) == true)
		{
			DataBank::Instance()->SetPlayerType((int)Player::PlayerTypeTuba);
			is_brass_scene = false;
			ChangeSceneStep(SceneStep::EndStep);
		}
	}
	else {
		m_param[5].texture_id = SelectCategoryTextureList::TrpFrame2;
		m_param[6].texture_id = SelectCategoryTextureList::FluteFrame2;
		m_param[7].texture_id = SelectCategoryTextureList::TubaFrame2;
		is_hit_mouse = false;
	}
}
