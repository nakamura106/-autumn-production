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
	LoadTexture("Res/Tex/SelectScene/SelectBg.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::SelectBgTex);
	LoadTexture("Res/Tex/SelectScene/BossSelect.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossSelectBottonTex);
	LoadTexture("Res/Tex/SelectScene/BrassSelect.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BrassSelectBottonTex);
	LoadTexture("Res/Tex/SelectScene/Boss1Image.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossMouseImageTex);
	LoadTexture("Res/Tex/SelectScene/Clear.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::ClearSymbolTex);
	LoadTexture("Res/Tex/SelectScene/Complete.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::CompleteSymbolTex);
	LoadTexture("Res/Tex/SelectScene/Time.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::TimeSymbolTex);
	LoadTexture("Res/Tex/SelectScene/Spotlight.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::SpotlightTex);
	LoadTexture("Res/Tex/SelectScene/NumberCollected.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::NumberCollectedTex);
	LoadTexture("Res/Tex/SelectScene/BossFrame/MouseFrame1.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossMouseFrame1);
	LoadTexture("Res/Tex/SelectScene/BossFrame/MouseFrame2.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossMouseFrame2);
	LoadTexture("Res/Tex/SelectScene/BossFrame/BirdFrame1.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossBirdFrame1);
	LoadTexture("Res/Tex/SelectScene/BossFrame/BirdFrame2.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossBirdFrame2);
	LoadTexture("Res/Tex/SelectScene/BossFrame/BirdFrame3.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossBirdFrame3);
	LoadTexture("Res/Tex/SelectScene/BossFrame/GorillaFrame1.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossGorillaFrame1);
	LoadTexture("Res/Tex/SelectScene/BossFrame/GorillaFrame2.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossGorillaFrame2);
	LoadTexture("Res/Tex/SelectScene/BossFrame/GorillaFrame3.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::BossGorillaFrame3);
	LoadTexture("Res/Tex/SelectScene/BrassFrame/TrpFrame1.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::TrpFrame1);
	LoadTexture("Res/Tex/SelectScene/BrassFrame/TrpFrame2.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::TrpFrame2);
	LoadTexture("Res/Tex/SelectScene/BrassFrame/FluteFrame1.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::FluteFrame1);
	LoadTexture("Res/Tex/SelectScene/BrassFrame/FluteFrame2.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::FluteFrame2);
	LoadTexture("Res/Tex/SelectScene/BrassFrame/FluteFrame3.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::FluteFrame3);
	LoadTexture("Res/Tex/SelectScene/BrassFrame/TubaFrame1.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::TubaFrame1);
	LoadTexture("Res/Tex/SelectScene/BrassFrame/TubaFrame2.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::TubaFrame2);
	LoadTexture("Res/Tex/SelectScene/BrassFrame/TubaFrame3.png", TEXTURE_CATEGORY_SELECT, SelectCategoryTextureList::TubaFrame3);


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
	m_param[7].texture_id = SelectCategoryTextureList::BossGorillaFrame3;

	if (m_pos[5].x < m_mouse_pos.x && m_mouse_pos.x < m_pos[5].x + 349.0f
		&& m_pos[5].y < m_mouse_pos.y && m_mouse_pos.y < m_pos[5].y + 349.0f) {
		m_param[6].texture_id = SelectCategoryTextureList::BossBirdFrame2;
		m_param[5].texture_id = SelectCategoryTextureList::BossMouseFrame1;
		m_pos[8].x = m_pos[5].x;
		is_hit_mouse = true;
		if (OnMouseDown(Left) == true)
		{
			is_brass_scene = true;
		}
	}
	else if (m_pos[6].x < m_mouse_pos.x && m_mouse_pos.x < m_pos[6].x + 349.0f
		&& m_pos[6].y < m_mouse_pos.y && m_mouse_pos.y < m_pos[6].y + 349.0f) {
		m_param[5].texture_id = SelectCategoryTextureList::BossMouseFrame2;
		m_param[6].texture_id = SelectCategoryTextureList::BossBirdFrame1;
		m_pos[8].x = m_pos[6].x;
		is_hit_mouse = true;
		if (OnMouseDown(Left) == true)
		{
			is_brass_scene = true;
		}
	}
	else {
		m_param[5].texture_id = SelectCategoryTextureList::BossMouseFrame2;
		m_param[6].texture_id = SelectCategoryTextureList::BossBirdFrame2;
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
		m_pos[8].x = m_pos[5].x;
		is_hit_mouse = true;
		if (GetKey(ONE_KEY)==true&&OnMouseDown(Left) == true)
		{
			DataBank::Instance()->SetPlayerType((int)Player::PlayerTypeTrumpet);
			ChangeSceneStep(SceneStep::EndStep);
		}
		if (GetKey(TWO_KEY) == true && OnMouseDown(Left) == true)
		{
			DataBank::Instance()->SetPlayerType((int)Player::PlayerTypeFlute);
			ChangeSceneStep(SceneStep::EndStep);
		}
		if (GetKey(THREE_KEY) == true && OnMouseDown(Left) == true)
		{
			DataBank::Instance()->SetPlayerType((int)Player::PlayerTypeTuba);
			ChangeSceneStep(SceneStep::EndStep);
		}
	}
	else {
		m_param[5].texture_id = SelectCategoryTextureList::TrpFrame2;
		is_hit_mouse = false;
	}
}
